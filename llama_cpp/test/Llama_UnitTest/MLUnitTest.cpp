
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

#include <gtest/gtest.h>

#include <ML/NaiveBayesClassifier.h>
#include <ML/DecisionTreeClassifier.h>
#include <ML/LinearSVM.h>

#include <vector>

using llama::DecisionTreeClassifier;
using llama::LinearSVM;
using llama::NaiveBayesClassifier;

using std::vector;

TEST(MLUnitTest, NaiveBayesProducesProbabilityRange) {
    vector<vector<int>> features = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    vector<bool> labels = {false, false, true, true};
    NaiveBayesClassifier classifier(features, labels);

    const double positiveProbability = classifier.getProbability({1, 1}, true);
    const double negativeProbability = classifier.getProbability({1, 1}, false);

    EXPECT_GE(positiveProbability, 0.0);
    EXPECT_LE(positiveProbability, 1.0);
    EXPECT_GE(negativeProbability, 0.0);
    EXPECT_LE(negativeProbability, 1.0);
}

TEST(MLUnitTest, DecisionTreeFitsSimpleDataset) {
    DecisionTreeClassifier classifier;
    vector<vector<int>> features = {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {1, 2}, {1, 3}};
    vector<bool> labels = {false, false, true, true, true, true};

    classifier.fit(features, labels);

    EXPECT_TRUE(classifier.isTrained());
    EXPECT_DOUBLE_EQ(classifier.score(features, labels), 1.0);
    EXPECT_FALSE(classifier.predict({0, 9}));
    EXPECT_TRUE(classifier.predict({1, 9}));
    EXPECT_TRUE(classifier.predict({2, 0}));
}

TEST(MLUnitTest, LinearSVMFitsSeparableDataset) {
    LinearSVM svm(0.01, 0.01, 2000);
    vector<vector<double>> features = {
        {2.0, 2.0}, {2.0, 3.0}, {3.0, 2.0},
        {-2.0, -2.0}, {-2.0, -3.0}, {-3.0, -2.0}
    };
    vector<int> labels = {1, 1, 1, -1, -1, -1};

    svm.fit(features, labels);

    EXPECT_TRUE(svm.isTrained());
    EXPECT_GE(svm.score(features, labels), 0.99);
    EXPECT_EQ(svm.predict({2.5, 2.5}), 1);
    EXPECT_EQ(svm.predict({-2.5, -2.5}), -1);
}
