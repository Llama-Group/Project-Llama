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

#include <Search/IterativeSearch.h>
#include <Search/Search.h>

#include <vector>

using std::vector;

TEST(SearchUnitTest, LinearSearchFindsExpectedIndex) {
    vector<int> data = {1, 3, 5, 7, 9, 11};
    EXPECT_EQ(llama::linearSearch(data, 1), 0);
    EXPECT_EQ(llama::linearSearch(data, 11), 5);
    EXPECT_EQ(llama::linearSearch(data, 8), -1);
}

TEST(SearchUnitTest, BinarySearchFindsExpectedIndex) {
    vector<int> sortedData = {1, 3, 5, 7, 9, 11};
    EXPECT_EQ(llama::binarySearch(sortedData, 1), 0);
    EXPECT_EQ(llama::binarySearch(sortedData, 7), 3);
    EXPECT_EQ(llama::binarySearch(sortedData, 11), 5);
    EXPECT_EQ(llama::binarySearch(sortedData, 8), -1);
}

TEST(SearchUnitTest, IterativeSearchWrapsSearchFunctions) {
    vector<int> sortedData = {1, 3, 5, 7, 9, 11};
    llama::IterativeSearch<int> search;

    EXPECT_EQ(search.linear(sortedData, 5), 2);
    EXPECT_EQ(search.binary(sortedData, 9), 4);
}
