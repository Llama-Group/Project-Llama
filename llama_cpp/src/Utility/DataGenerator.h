
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

#ifndef LLAMA_CPP_SRC_UTILITY_DATAGENERATOR_H_
#define LLAMA_CPP_SRC_UTILITY_DATAGENERATOR_H_

#include <stdio.h>
#include <vector>
#include <random>
#include <string>

namespace llama {

class RandomData {
 public:
    RandomData() {}

    template<typename T>
    void generateRandomData(std::vector<T> *targetVector, int count);
};

template<>
void RandomData::generateRandomData<int>(std::vector<int> *targetVector, int count);

template<>
void RandomData::generateRandomData<double>(std::vector<double> *targetVector, int count);

template<>
void RandomData::generateRandomData<std::string>(std::vector<std::string> *targetVector, int count);

class ContinuousData {
 public:
    ContinuousData() {}

    template<typename T>
    void generateContinuousData(std::vector<T> *targetVector, int count, bool reverse);
};

template<>
void ContinuousData::generateContinuousData<int>(std::vector<int> *targetVector, int count, bool reverse);

template<>
void ContinuousData::generateContinuousData<int>(std::vector<int> *targetVector, int count, bool reverse);

template<>
void ContinuousData::generateContinuousData<int>(std::vector<int> *targetVector, int count, bool reverse);

}  // namespace llama

#endif  // LLAMA_CPP_SRC_UTILITY_DATAGENERATOR_H_
