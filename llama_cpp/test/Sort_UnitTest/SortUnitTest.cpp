
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
    SortObject<int> objInt1;
    SortObject<int> objInt2;

    SortObject<std::string> objString1;
    SortObject<std::string> objString2;

    // Not testing for double because if int passed, double will definately pass.
};

// Integer equal.
TEST_F(SortObjectTest, EqualInteger) {
    objInt1 = SortObject<int>(0);
    objInt2 = SortObject<int>(0);
    EXPECT_EQ(objInt1, objInt2);
    EXPECT_GE(objInt1, objInt2);
    EXPECT_LE(objInt1, objInt2);
    EXPECT_EQ(objInt1, objInt1);
    EXPECT_GE(objInt1, objInt1);
    EXPECT_LE(objInt1, objInt1);
}

// Integer greater than.
TEST_F(SortObjectTest, GreaterInteger) {
    objInt1 = SortObject<int>(100);
    objInt2 = SortObject<int>(0);
    EXPECT_GT(objInt1, objInt2);
    EXPECT_GE(objInt1, objInt2);
}

// Integer less than.
TEST_F(SortObjectTest, LessInteger) {
    objInt1 = SortObject<int>(0);
    objInt2 = SortObject<int>(200);
    EXPECT_LT(objInt1, objInt2);
    EXPECT_LE(objInt1, objInt2);
}

// std::string equal.
TEST_F(SortObjectTest, EqualString) {
    objString1 = SortObject<std::string>("abc");
    objString2 = SortObject<std::string>("abc");
    EXPECT_EQ(objString1, objString2);
    EXPECT_GE(objString1, objString2);
    EXPECT_LE(objString1, objString2);
    EXPECT_EQ(objString1, objString1);
    EXPECT_GE(objString1, objString1);
    EXPECT_LE(objString1, objString1);
}

// std::string greater than.
TEST_F(SortObjectTest, GreaterString) {
    objString1 = SortObject<std::string>("bcd");
    objString2 = SortObject<std::string>("abc");
    EXPECT_GT(objString1, objString2);
    EXPECT_GE(objString1, objString2);
}

// std::string less than.
TEST_F(SortObjectTest, LessString) {
    objString1 = SortObject<std::string>("abc");
    objString2 = SortObject<std::string>("bcd");
    EXPECT_LT(objString1, objString2);
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
    vector<int> randomInts, continuousInts, continuousIntsReversed, *randomIntsMassive;
    vector<double> randomDoubles, continuousDoubles, continuousDoublesReversed;
    vector<string> randomStrings, continuousStrings, continuousStringsReversed;
    
    llama::RandomData mRandomData = llama::RandomData();
    llama::ContinuousData mContinuousData = llama::ContinuousData();
    
    vector<int> randomIntsCorrect, continuousIntsCorrect, continuousIntsReversedCorrect, *randomIntsMassiveCorrect;
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
        
    virtual void SetUp() {
        mRandomData.generateRandomData(&randomInts, 10);
        mRandomData.generateRandomData(&randomDoubles, 10);
        mRandomData.generateRandomData(&randomStrings, 10);
        mContinuousData.generateContinuousData(&continuousInts, 10, false);
        mContinuousData.generateContinuousData(&continuousDoubles, 10, false);
        mContinuousData.generateContinuousData(&continuousStrings, 10, false);
        mContinuousData.generateContinuousData(&continuousIntsReversed, 10, true);
        mContinuousData.generateContinuousData(&continuousDoublesReversed, 10, true);
        mContinuousData.generateContinuousData(&continuousStringsReversed, 10, true);
        
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

        const int vecIntCount = 100000;
        
        randomIntsMassive = new vector<int>();
        
        mRandomData.generateRandomData(randomIntsMassive, vecIntCount);
        
        randomIntsMassiveCorrect = new vector<int>(*randomIntsMassive);
        
        copy(randomIntsMassive->begin(), randomIntsMassive->end(), randomIntsMassiveCorrect->begin());
        
        sort(randomIntsMassiveCorrect->begin(), randomIntsMassiveCorrect->end());
    }
    
    virtual void TearDown() {
        delete randomIntsMassive;
        delete randomIntsMassiveCorrect;
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

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

