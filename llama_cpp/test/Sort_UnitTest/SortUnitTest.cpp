
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

#include <vector>
#include <string>

using std::string;
using std::vector;

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


int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

