
//
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include <ML/NeuralNetwork.h>

#include <math.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <iostream>
#include <stdexcept>

using std::cerr;
using std::vector;

using llama::Layer;
using llama::NeuralNetwork;

// Layer Training and Calculating Methods.
vector<double> Layer::feedAndCalculate(vector<double> input) {
    if (ID != LAYER_ID_INPUT) {
        throw std::invalid_argument("This function can only be called from input layer.");
    }

    values = input;

    Layer *processingLayer = this;
    while (processingLayer->ID != LAYER_ID_OUTPUT) {
        processingLayer->next->updateAndCalculateValues(&processingLayer->values);
        processingLayer = processingLayer->next;
    }

    return processingLayer->values;
}

void Layer::backpropagation(std::vector<double> output) {
    if (ID != LAYER_ID_OUTPUT) {
        throw std::invalid_argument("This function can only be called from output layer.");
    }
    
    // Calculate delta output.
    std::transform(values.begin(), values.end(), output.begin(), deltas.begin(),
                   [](double v, double o) { return (o - v) * v * (1 - v); });
    std::vector<double> *outputDeltas = &(this->deltas);
    double sumDeltaOutput = std::accumulate(deltas.begin(), deltas.end(), 0);
    
    Layer *processingLayer = this;
    while (processingLayer->ID != LAYER_ID_INPUT) {
        processingLayer->updateBackWeights(&output, outputDeltas, sumDeltaOutput);
        processingLayer = processingLayer->prev;
    }
}

// Layer Private Methods.
void Layer::updateAndCalculateValues(vector<double> *previousValues) {
    int index = 0;
    for (auto const &c : backWeightsVectors) {
        double value = 0;
        for (int i = 0; i < previousValues->size(); ++i) {
            value += previousValues->at(i)*c[i];
        }
        values[index] = sigmoidFunction(value);
        index++;
    }
}

void Layer::updateBackWeights(std::vector<double> *targetValues,
                              std::vector<double> *outputDeltas,
                              double sumDeltaOutput) {
    if (prev != LAYER_ID_INPUT) {
    // Set previous layer's deltas.
    double sumThisDeltas = 0.0;
    if (ID != LAYER_ID_OUTPUT) {
        sumThisDeltas = std::accumulate(deltas.begin(), deltas.end(), 0.0);
    }
    int indexThisDelta = 0;
    for (auto vectorIt = backWeightsVectors.begin();
         vectorIt < backWeightsVectors.end();
         ++vectorIt) {
        int indexPrevDelta = 0;
        for (auto weighIt = vectorIt->begin(); weighIt < vectorIt->end(); ++weighIt) {
            prev->deltas[indexPrevDelta] += (ID == LAYER_ID_OUTPUT ?
                                             deltas[indexThisDelta] :
                                             sumDeltaOutput) *
                                            *weighIt;
            indexPrevDelta++;
        }
        indexThisDelta++;
    }
    // Add this layer's sum of deltas to each of prev layer's deltas,
    // and multiplies dSigmoid of each of prev layer's values.
    std::transform(prev->deltas.begin(), prev->deltas.end(), prev->values.begin(),
                   prev->deltas.begin(),
                  [&](double a, double b) { return (a + sumThisDeltas) * b * (1 - b); });
    }
    
    int indexThisValue = 0;
    for (auto vecIt = backWeightsVectors.begin();
         vecIt < backWeightsVectors.end();
         ++vecIt) {
        int indexPreviousValue = 0;
        for (auto weightIt = vecIt->begin(); weightIt < vecIt->end(); ++weightIt) {
            double prevDelta = deltas[indexThisValue] *
                               prev->values[indexPreviousValue];
            *weightIt -= learningRate * prevDelta;
            indexPreviousValue++;
        }
        indexThisValue++;
    }
}

double Layer::sigmoidFunction(double input) {
    return 1.0/(1.0+exp(input*-1));
}

double Layer::dSigmoidFunction(double s) {
    return s * (1 - s);
}

// NeuralNetwork Constructor.
NeuralNetwork::NeuralNetwork(std::vector<int> numLayerVector, bool bias) {
    this->bias = bias;

    int currNum = 0, prevNum = 0;

    int numLayers = static_cast<int>(numLayerVector.size())-1;

    // Setup Output Layer.
    currNum = numLayerVector.back();
    numLayerVector.pop_back();
    prevNum = numLayerVector.back();
    numLayerVector.pop_back();

    Layer *outputLayer = new Layer(this, generateRandomBackWeightVectors(currNum, prevNum), LAYER_ID_OUTPUT, nullptr);
    Layers.insert(Layers.begin(), outputLayer);

    // Setup Hidden Layers.
    int count = 1;
    while (count <= numLayers-1) {
        currNum = prevNum;
        prevNum = numLayerVector.back();
        numLayerVector.pop_back();

        Layer *hiddenLayer = new Layer(this, generateRandomBackWeightVectors(currNum, prevNum),
                                       numLayers - count, Layers.front());
        Layers.insert(Layers.begin(), hiddenLayer);

        count++;
    }

    // Setup Input Layer.
    vector<vector<double>> inputLayerWeight;
    for (int i = 0; i < numLayerVector[0]; i++) {
        inputLayerWeight.push_back({});
    }
    Layer *inputLayer = new Layer(this, inputLayerWeight, LAYER_ID_INPUT, Layers.front());
    Layers.insert(Layers.begin(), inputLayer);

    // Set prev pointers.
    inputLayer->setPrev(nullptr);
    Layer *temp = inputLayer;
    for (auto const &c : this->Layers) {
        if (c->getID() != 0) {
            c->setPrev(temp);
            temp = c;
        }
    }
}

// Forward Propagation.
std::vector<double> NeuralNetwork::feed(std::vector<double> input) {
    if (input.size() != Layers[0]->size()) {
        throw std::invalid_argument("Input size mismatch.");
    }

    return Layers.front()->feedAndCalculate(input);
}

// Back Propagation.
void NeuralNetwork::train(std::vector<double> input, std::vector<double> output) {
    if (input.size() != Layers.front()->size()) {
        throw std::invalid_argument("Input size mismatch.");
    }
    if (output.size() != Layers.back()->size()) {
        throw std::invalid_argument("Output size mismatch.");
    }
    // Must feed before train.
    feed(input);

    // Calculate total error.
    totalError = 0.0;
    for (auto it = Layers.back()->values.begin(); it < Layers.back()->values.end(); ++it) {
        totalError += pow(*it - output[std::distance(it, Layers.back()->values.begin())], 2) * 0.5;
    }

    // Train
    Layers.back()->backpropagation(output);
}

void NeuralNetwork::printNeuralNetwork() {
    // Print input layer first.
    std::cout << "Input:\t\t";
    std::for_each(Layers.front()->values.begin(),
                  Layers.front()->values.end(),
                  [](double i){ std::cout << i << "    "; });
    std::cout << '\n';

    Layer *printingLayer = Layers.front()->next;

    while (printingLayer != nullptr) {
        int node = 0;
        for (auto const &c : printingLayer->backWeightsVectors) {
            std::cout << "Node " << node << ":\t\t";
            std::for_each(c.begin(),
                          c.end(),
                          [](double i){ std::cout << i << "    "; });
            std::cout << '\n';
            node++;
        }
        std::cout << "Layer ID." << printingLayer->ID << ":\t";
        std::for_each(printingLayer->values.begin(),
                      printingLayer->values.end(),
                      [](double i){ std::cout << i << "    "; });
        std::cout << '\n';
        printingLayer = printingLayer->next;
    }
}

// Get the total error before latest train.
double NeuralNetwork::getTotalError() {
    return totalError;
}

// Get the most updated total error.
double NeuralNetwork::getTotalError(vector<double> input, vector<double> targets) {
    vector<double> outputs = feed(input);
    totalError = 0.0;
    for (auto it = outputs.begin(); it < outputs.end(); ++it) {
        totalError += pow(*it - targets[std::distance(it, outputs.begin())], 2) * 0.5;
    }
    return totalError;
}

// NeurualNetwork Private Methods.
vector<vector<double>> NeuralNetwork::generateRandomBackWeightVectors(int numNeurons, int numPreviousNeurons) {
    // Gaussian random engine
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(1.0, 0.1);

    std::random_device randDevice;
    std::uniform_int_distribution<int> distTrueRandom(0, 10);
    for (int i = 0; i < distTrueRandom(randDevice); ++i) {
        distribution(generator);
    }

    vector<vector<double>> retVec;

    for (int i = 0; i < numNeurons; ++i) {
        vector<double> tempVec = {};
        for (int j = 0; j < numPreviousNeurons /*+ static_cast<int>(bias)*/; ++j) {
            // tempVec.push_back(distribution(generator));
            tempVec.push_back(1);
        }
        retVec.push_back(tempVec);
    }

    return retVec;
}
