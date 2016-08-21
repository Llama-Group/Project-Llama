
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

    rawValues = input;
    values = input;

    Layer *processingLayer = this;
    while (processingLayer->ID != LAYER_ID_OUTPUT) {
        processingLayer->next->updateAndCalculateValues(&processingLayer->values);
        processingLayer = processingLayer->next;
    }

    return processingLayer->values;
}

void Layer::updateValueWithDelta(std::vector<double> output) {
    if (ID != LAYER_ID_OUTPUT) {
        throw std::invalid_argument("This function can only be called from output layer.");
    }
    // Calculate deltas for output layer.
    std::transform(output.begin(), output.end(), values.begin(), deltas.begin(), errorFunction);

    Layer *processingLayer = this;
    // Process until first layer (next to input layer).
    while (processingLayer->prev->ID != LAYER_ID_INPUT) {
        processingLayer->calculateDeltas(&processingLayer->prev->deltas);
        processingLayer = processingLayer->prev;
    }

    // Start from input layer + 1
    while (processingLayer != nullptr) {
        processingLayer->updateWeights(&processingLayer->prev->values);
        processingLayer = processingLayer->next;
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
        rawValues[index] = value;
        values[index] = sigmoidFunction(value);
        index++;
    }
}

void Layer::calculateDeltas(vector<double> *previousDeltas) {
    std::fill(previousDeltas->begin(), previousDeltas->end(), 0);
    int indexD = 0;
    for (auto const &c : backWeightsVectors) {
        int indexPD = 0;
        for (auto const &w : c) {
            previousDeltas->at(indexPD) += w * deltas[indexD];
            indexPD++;
        }
        indexD++;
    }
}

void Layer::updateWeights(std::vector<double> *previousValues) {
    int indexD = 0;
    for (auto const &c : backWeightsVectors) {
        int indexW = 0;
        for (auto const &w : c) {
            double var = learningRate * deltas.at(indexD) *
                dSigmoidFunction(rawValues[indexD]) *
                previousValues->at(indexW);
            std::cout << "[w-" << indexD << '-' << indexW << "] " << deltas[indexD] << '\n';
            backWeightsVectors[indexD][indexW] = w + var;
            indexW++;
        }
        indexD++;
    }
}

double Layer::sigmoidFunction(double input) {
    return 1.0/(1.0+exp(input*-1));
}

double Layer::dSigmoidFunction(double input) {
    double s = sigmoidFunction(input);
    return s * (1 - s);
}

// NeuralNetwork Constructor.
NeuralNetwork::NeuralNetwork(std::vector<int> numLayerVector) {
    int currNum = 0, prevNum = 0;

    int numLayers = static_cast<int>(numLayerVector.size())-1;

    // Setup Output Layer.
    currNum = numLayerVector.back();
    numLayerVector.pop_back();
    prevNum = numLayerVector.back();
    numLayerVector.pop_back();

    Layer *outputLayer = new Layer(generateRandomBackWeightVectors(currNum, prevNum), LAYER_ID_OUTPUT, nullptr);
    Layers.insert(Layers.begin(), outputLayer);

    // Setup Hidden Layers.
    int count = 1;
    while (count <= numLayers-1) {
        currNum = prevNum;
        prevNum = numLayerVector.back();
        numLayerVector.pop_back();

        Layer *hiddenLayer = new Layer(generateRandomBackWeightVectors(currNum, prevNum),
                                       numLayers - count, Layers.front());
        Layers.insert(Layers.begin(), hiddenLayer);

        count++;
    }

    // Setup Input Layer.
    vector<vector<double>> inputLayerWeight;
    for (int i = 0; i < numLayerVector[0]; i++) {
        inputLayerWeight.push_back({});
    }
    Layer *inputLayer = new Layer(inputLayerWeight, LAYER_ID_INPUT, Layers.front());
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

    Layers.back()->updateValueWithDelta(output);
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
        for (int j = 0; j < numPreviousNeurons; ++j) {
            // tempVec.push_back(distribution(generator));
            tempVec.push_back(1);
        }
        retVec.push_back(tempVec);
    }

    return retVec;
}
