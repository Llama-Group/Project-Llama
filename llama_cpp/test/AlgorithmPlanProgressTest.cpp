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
#include <ML/LinearSVM.h>
#include <Search/IterativeSearch.h>
#include <Search/Search.h>

#include <cstdlib>
#include <iostream>
#include <vector>

namespace {
bool expect(bool condition, const std::string& message) {
    if (!condition) {
        std::cerr << "[FAIL] " << message << std::endl;
        return false;
    }
    return true;
}

bool runSearchTests() {
    std::vector<int> data = {1, 3, 5, 7, 9, 11};
    llama::IterativeSearch<int> iterativeSearch;

    bool passed = true;
    passed &= expect(llama::linearSearch(data, 1) == 0, "Linear search should find the first element.");
    passed &= expect(llama::linearSearch(data, 11) == 5, "Linear search should find the last element.");
    passed &= expect(llama::linearSearch(data, 8) == -1, "Linear search should return -1 when target is absent.");
    passed &= expect(llama::binarySearch(data, 7) == 3, "Binary search should find middle element.");
    passed &= expect(llama::binarySearch(data, 2) == -1, "Binary search should return -1 when target is absent.");
    passed &= expect(iterativeSearch.binary(data, 9) == 4, "IterativeSearch wrapper should call binary search.");
    passed &= expect(iterativeSearch.linear(data, 5) == 2, "IterativeSearch wrapper should call linear search.");

    if (passed) {
        std::cout << "[PASS] Search algorithms" << std::endl;
    }
    return passed;
}

bool runDecisionTreeTests() {
    llama::DecisionTreeClassifier decisionTree;

    std::vector<std::vector<int>> features = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}, {1, 2}, {1, 3}
    };
    std::vector<bool> labels = {false, false, true, true, true, true};

    decisionTree.fit(features, labels);

    bool passed = true;
    passed &= expect(decisionTree.isTrained(), "Decision tree should be trained after fit.");
    passed &= expect(decisionTree.score(features, labels) == 1.0,
                     "Decision tree should perfectly classify the training set.");
    passed &= expect(decisionTree.predict(std::vector<int>{0, 9}) == false,
                     "Decision tree should predict false for feature[0] == 0.");
    passed &= expect(decisionTree.predict(std::vector<int>{1, 9}) == true,
                     "Decision tree should predict true for feature[0] == 1.");
    passed &= expect(decisionTree.predict(std::vector<int>{2, 0}) == true,
                     "Decision tree should fallback to majority class for unseen branch.");

    if (passed) {
        std::cout << "[PASS] Decision Tree" << std::endl;
    }
    return passed;
}

bool runLinearSVMTests() {
    llama::LinearSVM svm(0.01, 0.01, 2000);

    std::vector<std::vector<double>> features = {
        {2.0, 2.0}, {2.0, 3.0}, {3.0, 2.0},
        {-2.0, -2.0}, {-2.0, -3.0}, {-3.0, -2.0}
    };
    std::vector<int> labels = {1, 1, 1, -1, -1, -1};

    svm.fit(features, labels);

    bool passed = true;
    passed &= expect(svm.isTrained(), "Linear SVM should be trained after fit.");
    passed &= expect(svm.score(features, labels) >= 0.99,
                     "Linear SVM should separate linearly separable training data.");
    passed &= expect(svm.predict(std::vector<double>{2.5, 2.5}) == 1,
                     "Linear SVM should classify positive sample as +1.");
    passed &= expect(svm.predict(std::vector<double>{-2.5, -2.5}) == -1,
                     "Linear SVM should classify negative sample as -1.");

    std::vector<int> binaryLabels = {1, 1, 1, 0, 0, 0};
    svm.fit(features, binaryLabels);
    passed &= expect(svm.score(features, binaryLabels) >= 0.99,
                     "Linear SVM should support 0/1 labels.");

    if (passed) {
        std::cout << "[PASS] Linear SVM" << std::endl;
    }
    return passed;
}
}  // namespace

int main() {
    bool passed = true;
    passed &= runSearchTests();
    passed &= runDecisionTreeTests();
    passed &= runLinearSVMTests();

    if (!passed) {
        std::cerr << "Algorithm plan regression tests failed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Algorithm plan regression tests passed." << std::endl;
    return EXIT_SUCCESS;
}
