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

#ifndef LLAMA_CPP_SRC_ML_LINEARSVM_H_
#define LLAMA_CPP_SRC_ML_LINEARSVM_H_

#include <vector>

namespace llama {
class LinearSVM {
 public:
    LinearSVM(double learningRate = 0.01, double regularization = 0.01, int epochs = 1000);

    void fit(const std::vector<std::vector<double>>& features, const std::vector<int>& labels);
    int predict(const std::vector<double>& sample) const;
    std::vector<int> predict(const std::vector<std::vector<double>>& samples) const;
    double decisionFunction(const std::vector<double>& sample) const;
    double score(const std::vector<std::vector<double>>& features, const std::vector<int>& labels) const;

    const std::vector<double>& getWeights() const { return weights; }
    double getBias() const { return bias; }
    bool isTrained() const { return trained; }

 private:
    int normalizeLabel(int label) const;
    double dot(const std::vector<double>& sample) const;

    std::vector<double> weights;
    double bias = 0.0;
    double learningRate = 0.01;
    double regularization = 0.01;
    int epochs = 1000;
    bool trained = false;
};
}  // namespace llama

#endif  // LLAMA_CPP_SRC_ML_LINEARSVM_H_
