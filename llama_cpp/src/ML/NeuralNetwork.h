
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

#ifndef LLAMA_CPP_SRC_ML_NEURALNETWORK_H_
#define LLAMA_CPP_SRC_ML_NEURALNETWORK_H_

#include <iostream>
#include <random>
#include <vector>

#define LAYER_ID_INPUT 0
#define LAYER_ID_OUTPUT -1

#define LAYER_VALUE_TYPE_DEFAULT 0x0
#define LAYER_VALUE_TYPE_VALUE 0x10
#define LAYER_VALUE_TYPE_SIGMA 0x20

namespace llama {
class Layer {
    friend class NeuralNetwork;
 public:
    Layer() {}

    Layer(std::vector<std::vector<double>> backWeightsVectors, int ID, Layer *next) {
        this->ID = ID;

        this->next = next;

        this->backWeightsVectors = backWeightsVectors;

        neuronCount = (uint32_t)backWeightsVectors.size();
        values = std::vector<double>(neuronCount);
    }

    // Setter
    void setPrev(Layer *prev) {
        this->prev = prev;
    }

    // Accesser
    int getID() { return ID; }
    Layer *getPrev() { return prev; }
    Layer *getNext() { return next; }
    std::vector<double> getValues() { return values; }
    int size() { return neuronCount; }

 private:
    int ID;

    Layer *prev;
    Layer *next;

    std::vector<std::vector<double>> backWeightsVectors;
    uint32_t neuronCount;
    
    uint8_t layerValueType = LAYER_VALUE_TYPE_DEFAULT;

    // Can only be called in input layer.
    std::vector<double> feedAndCalculate(std::vector<double> input);
    
    // Can only be called in output layer.
    void updateValueWithSigma(std::vector<double> output);

    std::vector<double> values;
    void updateAndCalculateValues(std::vector<double> previousValues);

    // Sigmoid function.
    double sigmoidFunction(double input);
};

class NeuralNetwork {
 public:
    NeuralNetwork() {}

    ~NeuralNetwork() {
        for (auto const &c : this->Layers) {
            delete c;
        }
    }

    explicit NeuralNetwork(std::vector<int>numLayerVector);

    // Forward Propagation
    std::vector<double> feed(std::vector<double> input);
    
    // Back Propagation
    void train(std::vector<double> input, std::vector<double> output);

    int size() { return Layers.size(); }
    
 private:
    std::vector<Layer *> Layers;

    std::vector<std::vector<double>> generateRandomBackWeightVectors(int numNeurons, int numPreviousNeurons);
};
}  // namespace llama

#endif  // LLAMA_CPP_SRC_ML_NEURALNETWORK_H_
