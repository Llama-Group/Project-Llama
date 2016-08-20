
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

#include <iostream>
#include <stdexcept>

using std::cerr;
using std::vector;

using llama::Layer;
using llama::NeuralNetwork;

// Layer Public Methods.
vector<double> Layer::feedAndCalculate(vector<double> input) {
    if (ID != 0) {
        throw std::invalid_argument("feedAndCalculate can only be called from input layer.");
    }

    values = input;

    Layer *processingLayer = this;
    while (processingLayer->ID != -1) {
        processingLayer->next->updateAndCalculateValues(processingLayer->values);
        processingLayer = processingLayer->next;
    }

    return processingLayer->values;
}

// Layer Private Methods.
void Layer::updateAndCalculateValues(vector<double> previousValues) {
    for (auto const &c : backWeightsVectors) {
        double value = 0;
        for (int i = 0; i < previousValues.size(); ++i) {
            value += previousValues[i]*c[i];
        }
        values.push_back(sigmoidFunction(value));
    }
}

double Layer::sigmoidFunction(double input) {
    return 1.0/(1.0+exp(input*-1));
}

// NeuralNetwork Constructor.
NeuralNetwork::NeuralNetwork(std::vector<int>numLayerVector)
{
    int currNum=0, prevNum=0;

    int numLayers = (int)numLayerVector.size()-1;

    // Setup Output Layer.
    currNum = numLayerVector.back();
    numLayerVector.pop_back();
    prevNum = numLayerVector.back();
    numLayerVector.pop_back();

    Layer *outputLayer = new Layer(generateRandomBackWeightVectors(currNum, prevNum), -1, nullptr);
    Layers.insert(Layers.begin(), outputLayer);

    // Setup Hidden Layers.
    int count = 1;
    while (count <= numLayers-1)
    {
        currNum = prevNum;
        prevNum = numLayerVector.back();
        numLayerVector.pop_back();

        Layer *hiddenLayer = new Layer(generateRandomBackWeightVectors(currNum, prevNum), numLayers-count, Layers.front());
        Layers.insert(Layers.begin(), hiddenLayer);

        count ++;
    }

    // Setup Input Layer.
    Layer *inputLayer = new Layer({}, 0, Layers.front());
    Layers.insert(Layers.begin(), inputLayer);

    // Set prev pointers.
    inputLayer->setPrev(nullptr);
    Layer *temp = inputLayer;
    for (auto const &c : this->Layers) {
        if (c->getID()!=0) {
            c->setPrev(temp);
            temp = c;
        }
    }
}

// NeurualNetwork Private Methods.
vector<vector<double>> NeuralNetwork::generateRandomBackWeightVectors(int numNeurons, int numPreviousNeurons) {
    // Gaussian random engine
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(1.0,0.1);

    std::random_device randDevice;
    std::uniform_int_distribution<int> distTrueRandom(0,10);
    for (int i = 0; i < distTrueRandom(randDevice); ++i) {
        distribution(generator);
    }

    vector<vector<double>> retVec;

    for (int i = 0; i < numNeurons; ++i) {
        vector<double> tempVec = {};
        for (int j = 0; j < numPreviousNeurons; ++j) {
            tempVec.push_back(distribution(generator));
        }
        retVec.push_back(tempVec);
    }

    return retVec;
}
