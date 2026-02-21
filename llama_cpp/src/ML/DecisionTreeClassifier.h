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

#ifndef LLAMA_CPP_SRC_ML_DECISIONTREECLASSIFIER_H_
#define LLAMA_CPP_SRC_ML_DECISIONTREECLASSIFIER_H_

#include <map>
#include <memory>
#include <vector>

namespace llama {
class DecisionTreeClassifier {
 public:
    DecisionTreeClassifier() {}

    void fit(const std::vector<std::vector<int>>& features, const std::vector<bool>& labels);
    bool predict(const std::vector<int>& sample) const;
    std::vector<bool> predict(const std::vector<std::vector<int>>& samples) const;
    double score(const std::vector<std::vector<int>>& features, const std::vector<bool>& labels) const;

    bool isTrained() const { return trained; }

 private:
    struct Node {
        bool isLeaf = true;
        bool label = false;
        bool majorityLabel = false;
        int featureIndex = -1;
        std::map<int, std::unique_ptr<Node>> children;
    };

    std::unique_ptr<Node> root;
    bool trained = false;
    int featureCount = 0;

    std::unique_ptr<Node> buildTree(const std::vector<int>& sampleIndices,
                                    const std::vector<int>& availableFeatures,
                                    const std::vector<std::vector<int>>& features,
                                    const std::vector<bool>& labels) const;

    bool predictFromNode(const Node* node, const std::vector<int>& sample) const;
    double entropy(const std::vector<int>& sampleIndices, const std::vector<bool>& labels) const;
    double informationGain(const std::vector<int>& sampleIndices, int featureIndex,
                           const std::vector<std::vector<int>>& features,
                           const std::vector<bool>& labels) const;
    bool majorityLabelForSamples(const std::vector<int>& sampleIndices,
                                 const std::vector<bool>& labels) const;
    bool hasSingleClass(const std::vector<int>& sampleIndices, const std::vector<bool>& labels) const;
};
}  // namespace llama

#endif  // LLAMA_CPP_SRC_ML_DECISIONTREECLASSIFIER_H_
