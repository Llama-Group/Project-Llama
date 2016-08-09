
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License,Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at:
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing,software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#ifndef LLAMA_CPP_SRC_ML_NAIVEBAYESCLASSIFIER_H_
#define LLAMA_CPP_SRC_ML_NAIVEBAYESCLASSIFIER_H_

#include <iostream>
#include <vector>

namespace llama {
class NaiveBayesClassifier {
 public:
    NaiveBayesClassifier();

    NaiveBayesClassifier(std::vector<std::vector<int>> Xs, std::vector<bool> Y) {
        this->features = Xs;
        this->featureClass = Y;
    }

    double getEstimation(std::vector<int>X, bool Y);
    double getProbability(std::vector<int>X, bool Y);

    void addTrainData(std::vector<int>X, bool Y) {
        features.push_back(X);
        featureClass.push_back(Y);
    }

 private:
    std::vector<std::vector<int>> features;
    std::vector<bool> featureClass;

    double theta;
    double pi;

    double getTheta(int feature, int featureValue, bool targetClass);
    double getPi(bool targetClass);
};
}  // namespace llama

#endif  // LLAMA_CPP_SRC_ML_NAIVEBAYESCLASSIFIER_H_
