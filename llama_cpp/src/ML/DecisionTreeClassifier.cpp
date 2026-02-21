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

#include <ML/DecisionTreeClassifier.h>

#include <cmath>
#include <stdexcept>

namespace {
double safeLog2(double value) {
    return std::log(value) / std::log(2.0);
}
}  // namespace

void llama::DecisionTreeClassifier::fit(const std::vector<std::vector<int>>& features,
                                        const std::vector<bool>& labels) {
    if (features.empty()) {
        throw std::invalid_argument("Features must not be empty.");
    }
    if (features.size() != labels.size()) {
        throw std::invalid_argument("Features and labels size mismatch.");
    }

    featureCount = static_cast<int>(features[0].size());
    if (featureCount <= 0) {
        throw std::invalid_argument("Feature count must be positive.");
    }
    for (const std::vector<int>& sample : features) {
        if (static_cast<int>(sample.size()) != featureCount) {
            throw std::invalid_argument("Inconsistent feature size in training data.");
        }
    }

    std::vector<int> sampleIndices(features.size());
    for (std::size_t i = 0; i < features.size(); ++i) {
        sampleIndices[i] = static_cast<int>(i);
    }

    std::vector<int> availableFeatures(featureCount);
    for (int i = 0; i < featureCount; ++i) {
        availableFeatures[i] = i;
    }

    root = buildTree(sampleIndices, availableFeatures, features, labels);
    trained = true;
}

bool llama::DecisionTreeClassifier::predict(const std::vector<int>& sample) const {
    if (!trained || root.get() == nullptr) {
        throw std::logic_error("Model is not trained.");
    }
    if (static_cast<int>(sample.size()) != featureCount) {
        throw std::invalid_argument("Sample feature size mismatch.");
    }
    return predictFromNode(root.get(), sample);
}

std::vector<bool> llama::DecisionTreeClassifier::predict(
    const std::vector<std::vector<int>>& samples) const {
    std::vector<bool> predictions;
    predictions.reserve(samples.size());
    for (const std::vector<int>& sample : samples) {
        predictions.push_back(predict(sample));
    }
    return predictions;
}

double llama::DecisionTreeClassifier::score(const std::vector<std::vector<int>>& features,
                                            const std::vector<bool>& labels) const {
    if (features.size() != labels.size()) {
        throw std::invalid_argument("Features and labels size mismatch.");
    }
    if (features.empty()) {
        return 0.0;
    }

    int correct = 0;
    for (std::size_t i = 0; i < features.size(); ++i) {
        if (predict(features[i]) == labels[i]) {
            ++correct;
        }
    }
    return static_cast<double>(correct) / static_cast<double>(features.size());
}

std::unique_ptr<llama::DecisionTreeClassifier::Node>
llama::DecisionTreeClassifier::buildTree(const std::vector<int>& sampleIndices,
                                         const std::vector<int>& availableFeatures,
                                         const std::vector<std::vector<int>>& features,
                                         const std::vector<bool>& labels) const {
    std::unique_ptr<Node> node(new Node());
    node->majorityLabel = majorityLabelForSamples(sampleIndices, labels);

    if (sampleIndices.empty()) {
        node->isLeaf = true;
        node->label = node->majorityLabel;
        return node;
    }

    if (hasSingleClass(sampleIndices, labels) || availableFeatures.empty()) {
        node->isLeaf = true;
        node->label = node->majorityLabel;
        return node;
    }

    int bestFeature = -1;
    double bestGain = -1.0;
    for (int featureIndex : availableFeatures) {
        double gain = informationGain(sampleIndices, featureIndex, features, labels);
        if (gain > bestGain) {
            bestGain = gain;
            bestFeature = featureIndex;
        }
    }

    if (bestFeature < 0 || bestGain <= 0.0) {
        node->isLeaf = true;
        node->label = node->majorityLabel;
        return node;
    }

    node->isLeaf = false;
    node->featureIndex = bestFeature;

    std::vector<int> remainingFeatures;
    remainingFeatures.reserve(availableFeatures.size());
    for (int featureIndex : availableFeatures) {
        if (featureIndex != bestFeature) {
            remainingFeatures.push_back(featureIndex);
        }
    }

    std::map<int, std::vector<int>> partitions;
    for (int sampleIndex : sampleIndices) {
        partitions[features[sampleIndex][bestFeature]].push_back(sampleIndex);
    }

    for (const auto& partition : partitions) {
        node->children[partition.first] = buildTree(
            partition.second, remainingFeatures, features, labels);
    }

    if (node->children.empty()) {
        node->isLeaf = true;
        node->label = node->majorityLabel;
    }

    return node;
}

bool llama::DecisionTreeClassifier::predictFromNode(const Node* node,
                                                    const std::vector<int>& sample) const {
    if (node->isLeaf) {
        return node->label;
    }

    const auto child = node->children.find(sample[node->featureIndex]);
    if (child == node->children.end() || child->second.get() == nullptr) {
        return node->majorityLabel;
    }
    return predictFromNode(child->second.get(), sample);
}

double llama::DecisionTreeClassifier::entropy(const std::vector<int>& sampleIndices,
                                              const std::vector<bool>& labels) const {
    if (sampleIndices.empty()) {
        return 0.0;
    }

    int positives = 0;
    for (int index : sampleIndices) {
        if (labels[index]) {
            ++positives;
        }
    }

    const double total = static_cast<double>(sampleIndices.size());
    const double positiveRatio = static_cast<double>(positives) / total;
    const double negativeRatio = 1.0 - positiveRatio;

    double result = 0.0;
    if (positiveRatio > 0.0) {
        result -= positiveRatio * safeLog2(positiveRatio);
    }
    if (negativeRatio > 0.0) {
        result -= negativeRatio * safeLog2(negativeRatio);
    }
    return result;
}

double llama::DecisionTreeClassifier::informationGain(
    const std::vector<int>& sampleIndices, int featureIndex,
    const std::vector<std::vector<int>>& features,
    const std::vector<bool>& labels) const {
    if (sampleIndices.empty()) {
        return 0.0;
    }

    const double baseEntropy = entropy(sampleIndices, labels);
    std::map<int, std::vector<int>> partitions;
    for (int sampleIndex : sampleIndices) {
        partitions[features[sampleIndex][featureIndex]].push_back(sampleIndex);
    }

    double remainder = 0.0;
    const double total = static_cast<double>(sampleIndices.size());
    for (const auto& partition : partitions) {
        const double portion = static_cast<double>(partition.second.size()) / total;
        remainder += portion * entropy(partition.second, labels);
    }

    return baseEntropy - remainder;
}

bool llama::DecisionTreeClassifier::majorityLabelForSamples(
    const std::vector<int>& sampleIndices, const std::vector<bool>& labels) const {
    int positives = 0;
    for (int index : sampleIndices) {
        if (labels[index]) {
            ++positives;
        }
    }

    return positives * 2 >= static_cast<int>(sampleIndices.size());
}

bool llama::DecisionTreeClassifier::hasSingleClass(
    const std::vector<int>& sampleIndices, const std::vector<bool>& labels) const {
    if (sampleIndices.empty()) {
        return true;
    }

    const bool first = labels[sampleIndices.front()];
    for (int index : sampleIndices) {
        if (labels[index] != first) {
            return false;
        }
    }
    return true;
}
