
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

#include <ML/NaiveBayesClassifier.h>

#include <algorithm>
#include <vector>

using std::vector;

double llama::NaiveBayesClassifier::getTheta(int feature, int featureValue, bool targetClass) {
    const int l = 1;

    double theta = 0;
    vector<int> distinct;
    int countY = 0;
    auto currentFeature = this->features[feature];
    for (auto it = currentFeature.begin(); it != currentFeature.end(); ++it) {
        if (std::find(distinct.begin(), distinct.end(), *it) == distinct.end()) {
            distinct.push_back(*it);
        }
        if (this->featureClass[distance(currentFeature.begin(), it)] == targetClass) {
            countY++;
            if (*it == featureValue)
                theta++;
        }
    }

    theta += l;
    theta = theta/(l*distinct.size() + countY);
    return theta;
}

double llama::NaiveBayesClassifier::getPi(bool targetClass) {
    double pi = 0;

    for (const bool &c : this->featureClass) {
        if (c == targetClass) {
            pi++;
        }
    }

    pi = pi/this->featureClass.size();

    return pi;
}

double llama::NaiveBayesClassifier::getEstimation(std::vector<int> X, bool Y) {
    double retVal = 1;

    for (auto it = X.begin(); it != X.end(); ++it) {
        retVal *= this->getTheta(static_cast<int>(distance(X.begin(), it)), *it, Y);
    }

    retVal *= this->getPi(Y);

    return retVal;
}

double llama::NaiveBayesClassifier::getProbability(std::vector<int> X, bool Y) {
    double eY = this->getEstimation(X, Y);
    return eY/(eY+this->getEstimation(X, !Y));
}
