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

#include <ML/LinearSVM.h>

#include <stdexcept>

llama::LinearSVM::LinearSVM(double learningRate, double regularization, int epochs) {
    if (learningRate <= 0.0) {
        throw std::invalid_argument("Learning rate must be positive.");
    }
    if (regularization < 0.0) {
        throw std::invalid_argument("Regularization must be non-negative.");
    }
    if (epochs <= 0) {
        throw std::invalid_argument("Epochs must be positive.");
    }

    this->learningRate = learningRate;
    this->regularization = regularization;
    this->epochs = epochs;
}

void llama::LinearSVM::fit(const std::vector<std::vector<double>>& features,
                           const std::vector<int>& labels) {
    if (features.empty()) {
        throw std::invalid_argument("Features must not be empty.");
    }
    if (features.size() != labels.size()) {
        throw std::invalid_argument("Features and labels size mismatch.");
    }

    const std::size_t featureCount = features[0].size();
    if (featureCount == 0) {
        throw std::invalid_argument("Feature count must be positive.");
    }
    for (const std::vector<double>& sample : features) {
        if (sample.size() != featureCount) {
            throw std::invalid_argument("Inconsistent feature size in training data.");
        }
    }

    weights.assign(featureCount, 0.0);
    bias = 0.0;

    for (int epoch = 0; epoch < epochs; ++epoch) {
        const double eta = learningRate / (1.0 + 0.01 * static_cast<double>(epoch));
        for (std::size_t i = 0; i < features.size(); ++i) {
            const int yi = normalizeLabel(labels[i]);
            const double margin = static_cast<double>(yi) * (dot(features[i]) + bias);
            if (margin >= 1.0) {
                for (std::size_t j = 0; j < featureCount; ++j) {
                    weights[j] -= eta * (2.0 * regularization * weights[j]);
                }
            } else {
                for (std::size_t j = 0; j < featureCount; ++j) {
                    weights[j] -= eta * ((2.0 * regularization * weights[j]) -
                                          static_cast<double>(yi) * features[i][j]);
                }
                bias += eta * static_cast<double>(yi);
            }
        }
    }

    trained = true;
}

int llama::LinearSVM::predict(const std::vector<double>& sample) const {
    if (!trained) {
        throw std::logic_error("Model is not trained.");
    }
    return decisionFunction(sample) >= 0.0 ? 1 : -1;
}

std::vector<int> llama::LinearSVM::predict(const std::vector<std::vector<double>>& samples) const {
    std::vector<int> predictions;
    predictions.reserve(samples.size());
    for (const std::vector<double>& sample : samples) {
        predictions.push_back(predict(sample));
    }
    return predictions;
}

double llama::LinearSVM::decisionFunction(const std::vector<double>& sample) const {
    if (weights.empty()) {
        throw std::logic_error("Model is not trained.");
    }
    if (sample.size() != weights.size()) {
        throw std::invalid_argument("Sample feature size mismatch.");
    }
    return dot(sample) + bias;
}

double llama::LinearSVM::score(const std::vector<std::vector<double>>& features,
                               const std::vector<int>& labels) const {
    if (features.size() != labels.size()) {
        throw std::invalid_argument("Features and labels size mismatch.");
    }
    if (features.empty()) {
        return 0.0;
    }

    int correct = 0;
    for (std::size_t i = 0; i < features.size(); ++i) {
        if (predict(features[i]) == normalizeLabel(labels[i])) {
            ++correct;
        }
    }

    return static_cast<double>(correct) / static_cast<double>(features.size());
}

int llama::LinearSVM::normalizeLabel(int label) const {
    return label > 0 ? 1 : -1;
}

double llama::LinearSVM::dot(const std::vector<double>& sample) const {
    if (sample.size() != weights.size()) {
        throw std::invalid_argument("Sample feature size mismatch.");
    }

    double result = 0.0;
    for (std::size_t i = 0; i < sample.size(); ++i) {
        result += sample[i] * weights[i];
    }
    return result;
}
