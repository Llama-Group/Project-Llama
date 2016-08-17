
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
#include <Sort/Sort.h>
#include <Utility/DataGenerator.h>
#include <Sort/BruteForceSort.h>
#include <Sort/InsertionSort.h>
#include <Sort/BubbleSort.h>
#include <Sort/SelectionSort.h>

#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::vector;
using std::copy;
using std::sort;

using llama::SortObject;
using llama::Sort;

//
// SortObject Test.
//

struct SortObjectTest : public ::testing::Test {
    llama::DataGenerator mDataGenerator = llama::DataGenerator();

    SortObject<int> objInt1;
    SortObject<int> objInt2;

    SortObject<double> objDouble1;
    SortObject<double> objDouble2;

    SortObject<std::string> objString1;
    SortObject<std::string> objString2;
};

// Integer equal.
TEST_F(SortObjectTest, EqualInteger) {
    int refInt = mDataGenerator.generateSingleDatum<int>();
    objInt1 = SortObject<int>(refInt);
    objInt2 = SortObject<int>(mDataGenerator.generateSingleDatum(&refInt, EQ));
    EXPECT_EQ(objInt1, objInt2);
    EXPECT_GE(objInt1, objInt2);
    EXPECT_LE(objInt1, objInt2);
    EXPECT_EQ(objInt1, objInt1);
    EXPECT_GE(objInt1, objInt1);
    EXPECT_LE(objInt1, objInt1);
}

// Integer greater than.
TEST_F(SortObjectTest, GreaterInteger) {
    int refInt = mDataGenerator.generateSingleDatum<int>();
    objInt1 = SortObject<int>(refInt);
    objInt2 = SortObject<int>(mDataGenerator.generateSingleDatum(&refInt, LT));
    EXPECT_GT(objInt1, objInt2);
    objInt2 = SortObject<int>(mDataGenerator.generateSingleDatum(&refInt, LE));
    EXPECT_GE(objInt1, objInt2);
}

// Integer less than.
TEST_F(SortObjectTest, LessInteger) {
    int refInt = mDataGenerator.generateSingleDatum<int>();
    objInt1 = SortObject<int>(refInt);
    objInt2 = SortObject<int>(mDataGenerator.generateSingleDatum(&refInt, GT));
    EXPECT_LT(objInt1, objInt2);
    objInt2 = SortObject<int>(mDataGenerator.generateSingleDatum(&refInt, GE));
    EXPECT_LE(objInt1, objInt2);
}

// Double equal.
TEST_F(SortObjectTest, EqualDouble) {
    double refDouble = mDataGenerator.generateSingleDatum<double>();
    objDouble1 = SortObject<double>(refDouble);
    objDouble2 = SortObject<double>(mDataGenerator.generateSingleDatum(&refDouble, EQ));
    EXPECT_EQ(objDouble1, objDouble2);
    EXPECT_GE(objDouble1, objDouble2);
    EXPECT_LE(objDouble1, objDouble2);
    EXPECT_EQ(objDouble1, objDouble1);
    EXPECT_GE(objDouble1, objDouble1);
    EXPECT_LE(objDouble1, objDouble1);
}

// Double greater than.
TEST_F(SortObjectTest, GreaterDouble) {
    double refDouble = mDataGenerator.generateSingleDatum<double>();
    objDouble1 = SortObject<double>(refDouble);
    objDouble2 = SortObject<double>(mDataGenerator.generateSingleDatum(&refDouble, LT));
    EXPECT_GT(objDouble1, objDouble2);
    objDouble2 = SortObject<double>(mDataGenerator.generateSingleDatum(&refDouble, LE));
    EXPECT_GE(objDouble1, objDouble2);
}

// Double less than.
TEST_F(SortObjectTest, LessDouble) {
    double refDouble = mDataGenerator.generateSingleDatum<double>();
    objDouble1 = SortObject<double>(refDouble);
    objDouble2 = SortObject<double>(mDataGenerator.generateSingleDatum(&refDouble, GT));
    EXPECT_LT(objDouble1, objDouble2);
    objDouble2 = SortObject<double>(mDataGenerator.generateSingleDatum(&refDouble, GE));
    EXPECT_LE(objDouble1, objDouble2);
}

// std::string equal.
TEST_F(SortObjectTest, EqualString) {
    string refString = mDataGenerator.generateSingleDatum<string>();
    objString1 = SortObject<std::string>(refString);
    objString2 = SortObject<std::string>(mDataGenerator.generateSingleDatum(&refString, EQ));
    EXPECT_EQ(objString1, objString2);
    EXPECT_GE(objString1, objString2);
    EXPECT_LE(objString1, objString2);
    EXPECT_EQ(objString1, objString1);
    EXPECT_GE(objString1, objString1);
    EXPECT_LE(objString1, objString1);
}

// std::string greater than.
TEST_F(SortObjectTest, GreaterString) {
    string refString = mDataGenerator.generateSingleDatum<string>();
    objString1 = SortObject<std::string>(refString);
    objString2 = SortObject<std::string>(mDataGenerator.generateSingleDatum(&refString, GT));
    EXPECT_GT(objString1, objString2);
    objString2 = SortObject<std::string>(mDataGenerator.generateSingleDatum(&refString, GE));
    EXPECT_GE(objString1, objString2);
}

// std::string less than.
TEST_F(SortObjectTest, LessString) {
    string refString = mDataGenerator.generateSingleDatum<string>();
    objString1 = SortObject<std::string>(refString);
    objString2 = SortObject<std::string>(mDataGenerator.generateSingleDatum(&refString, LT));
    EXPECT_LT(objString1, objString2);
    objString2 = SortObject<std::string>(mDataGenerator.generateSingleDatum(&refString, LE));
    EXPECT_LE(objString1, objString2);
}

//
// Sort Abstract Class test.
//

struct SortAbstractClassTest : public ::testing::Test {
    Sort<int> objSort = Sort<int>();

    FRIEND_TEST(SortAbstractClassTest, Sort);
};

TEST_F(SortAbstractClassTest, CallVirtualFunction) {
    vector<int> v1 = {5, 4, 3, 2, 1};
    vector<int> v2(v1);
    testing::internal::CaptureStderr();
    objSort.performSort(&v1);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "Abstract function, do not call!\n") << "Virtual function not called.";
    EXPECT_EQ(v1, v2) << "Vector should not be changed.";
}

//
// Sort Correctness test.
//

struct SortCorrectnessTest : public ::testing::Test {
    vector<int> randomInts, continuousInts, continuousIntsReversed;
    vector<double> randomDoubles, continuousDoubles, continuousDoublesReversed;
    vector<string> randomStrings, continuousStrings, continuousStringsReversed;

    llama::DataGenerator mDataGenerator = llama::DataGenerator();

    vector<int> randomIntsCorrect, continuousIntsCorrect, continuousIntsReversedCorrect;
    vector<double> randomDoublesCorrect, continuousDoublesCorrect,
        continuousDoublesReversedCorrect;
    vector<string> randomStringsCorrect, continuousStringsCorrect,
        continuousStringsReversedCorrect;

    llama::BruteForceSort<int> intBF;
    llama::BruteForceSort<double> doubleBF;
    llama::BruteForceSort<string> stringBF;

    llama::InsertionSort<int> intIn;
    llama::InsertionSort<double> doubleIn;
    llama::InsertionSort<string> stringIn;

    llama::BubbleSort<int> intBu;
    llama::BubbleSort<double> doubleBu;
    llama::BubbleSort<string> stringBu;

    llama::SelectionSort<int> intSe;
    llama::SelectionSort<double> doubleSe;
    llama::SelectionSort<string> stringSe;

    void SetUp() override {
        mDataGenerator.generateRandomData(&randomInts, 10);
        mDataGenerator.generateRandomData(&randomDoubles, 10);
        mDataGenerator.generateRandomData(&randomStrings, 10);
        mDataGenerator.generateContinuousData(&continuousInts, 10, false);
        mDataGenerator.generateContinuousData(&continuousDoubles, 10, false);
        mDataGenerator.generateContinuousData(&continuousStrings, 10, false);
        mDataGenerator.generateContinuousData(&continuousIntsReversed, 10, true);
        mDataGenerator.generateContinuousData(&continuousDoublesReversed, 10, true);
        mDataGenerator.generateContinuousData(&continuousStringsReversed, 10, true);

        randomIntsCorrect = randomInts;
        randomDoublesCorrect = randomDoubles;
        randomStringsCorrect = randomStrings;
        continuousIntsCorrect = continuousInts;
        continuousDoublesCorrect = continuousDoubles;
        continuousStringsCorrect = continuousStrings;
        continuousIntsReversedCorrect = continuousIntsReversed;
        continuousDoublesReversedCorrect = continuousDoublesReversed;
        continuousStringsReversedCorrect = continuousStringsReversed;

        sort(randomIntsCorrect.begin(), randomIntsCorrect.end());
        sort(randomDoublesCorrect.begin(), randomDoublesCorrect.end());
        sort(randomStringsCorrect.begin(), randomStringsCorrect.end());
        sort(continuousIntsCorrect.begin(), continuousIntsCorrect.end());
        sort(continuousDoublesCorrect.begin(), continuousDoublesCorrect.end());
        sort(continuousStringsCorrect.begin(), continuousStringsCorrect.end());
        sort(continuousIntsReversedCorrect.begin(), continuousIntsReversedCorrect.end());
        sort(continuousDoublesReversedCorrect.begin(), continuousDoublesReversedCorrect.end());
        sort(continuousStringsReversedCorrect.begin(), continuousStringsReversedCorrect.end());
    }
};

// Testing for Brute Force Sort.
TEST_F(SortCorrectnessTest, BruteForceRandomIntsCorrectness) {
    intBF.performSort(&randomInts);
    EXPECT_EQ(randomIntsCorrect, randomInts);
}

TEST_F(SortCorrectnessTest, BruteForceRandomDoublesCorrectness) {
    doubleBF.performSort(&randomDoubles);
    EXPECT_EQ(randomDoublesCorrect, randomDoubles);
}

TEST_F(SortCorrectnessTest, BruteForceRandomStringsCorrectness) {
    stringBF.performSort(&randomStrings);
    EXPECT_EQ(randomStringsCorrect, randomStrings);
}

// Testing for Insertion Sort.
TEST_F(SortCorrectnessTest, InsertionRandomIntsCorrectness) {
    intIn.performSort(&randomInts);
    EXPECT_EQ(randomIntsCorrect, randomInts);
}

TEST_F(SortCorrectnessTest, InsertionRandomDoublesCorrectness) {
    doubleIn.performSort(&randomDoubles);
    EXPECT_EQ(randomDoublesCorrect, randomDoubles);
}

TEST_F(SortCorrectnessTest, InsertionRandomStringsCorrectness) {
    stringIn.performSort(&randomStrings);
    EXPECT_EQ(randomStringsCorrect, randomStrings);
}

// Testing for Bubble Sort.
TEST_F(SortCorrectnessTest, BubbleRandomIntsCorrectness) {
    intBu.performSort(&randomInts);
    EXPECT_EQ(randomIntsCorrect, randomInts);
}

TEST_F(SortCorrectnessTest, BubbleRandomDoublesCorrectness) {
    doubleBu.performSort(&randomDoubles);
    EXPECT_EQ(randomDoublesCorrect, randomDoubles);
}

TEST_F(SortCorrectnessTest, BubbleRandomStringsCorrectness) {
    stringBu.performSort(&randomStrings);
    EXPECT_EQ(randomStringsCorrect, randomStrings);
}

// Testing for Selection Sort.
TEST_F(SortCorrectnessTest, SelectionRandomIntsCorrectness) {
    intSe.performSort(&randomInts);
    EXPECT_EQ(randomIntsCorrect, randomInts);
}

TEST_F(SortCorrectnessTest, SelectionRandomDoublesCorrectness) {
    doubleSe.performSort(&randomDoubles);
    EXPECT_EQ(randomDoublesCorrect, randomDoubles);
}

TEST_F(SortCorrectnessTest, SelectionRandomStringsCorrectness) {
    stringSe.performSort(&randomStrings);
    EXPECT_EQ(randomStringsCorrect, randomStrings);
}


//
// Sort Massive Test
//

struct SortMassiveTest : public ::testing::Test {
    vector<int> *randomIntsMassive, *randomIntsMassiveCorrect;
    vector<int> *randomIntsSuperMassive, *randomIntsSuperMassiveCorrect;

    llama::DataGenerator mDataGenerator = llama::DataGenerator();

    llama::Sort<int> intSort;

    llama::BruteForceSort<int> intBF;
    llama::InsertionSort<int> intIn;
    llama::BubbleSort<int> intBu;
    llama::SelectionSort<int> intSe;

    void setupVector(vector<int> **m, vector<int> **mCorrect, int count) {
        *m = new vector<int>();

        mDataGenerator.generateRandomData(*m, count);

        *mCorrect = new vector<int>(**m);

        copy((*m)->begin(), (*m)->end(), (*mCorrect)->begin());

        sort((*mCorrect)->begin(), (*mCorrect)->end());
    }

    void SetUp() override {
        setupVector(&randomIntsMassive, &randomIntsMassiveCorrect, 10000);
        setupVector(&randomIntsSuperMassive, &randomIntsSuperMassiveCorrect, 100000);
    }

    void TearDown() override {
        delete randomIntsMassive;
        delete randomIntsMassiveCorrect;

        delete randomIntsSuperMassive;
        delete randomIntsSuperMassiveCorrect;
    }
};

TEST_F(SortMassiveTest, SortAbstractClassMassive) {
    vector<int> *originalVector = new vector<int>(*randomIntsMassive);
    intSort.performSort(randomIntsMassive);
    ASSERT_EQ(*originalVector, *randomIntsMassive);
    delete originalVector;
}

TEST_F(SortMassiveTest, BruteForceMassive) {
    intBF.performSort(randomIntsMassive);
    EXPECT_EQ(*randomIntsMassiveCorrect, *randomIntsMassive);
}

TEST_F(SortMassiveTest, InsertionMassive) {
    intIn.performSort(randomIntsMassive);
    EXPECT_EQ(*randomIntsMassiveCorrect, *randomIntsMassive);
}

TEST_F(SortMassiveTest, BubbleMassive) {
    intBu.performSort(randomIntsMassive);
    EXPECT_EQ(*randomIntsMassiveCorrect, *randomIntsMassive);
}

TEST_F(SortMassiveTest, SelectionMassive) {
    intSe.performSort(randomIntsMassive);
    EXPECT_EQ(*randomIntsMassiveCorrect, *randomIntsMassive);
}
