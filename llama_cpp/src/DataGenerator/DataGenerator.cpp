
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

#include <vector>
#include <ctime>

#include "DataGenerator.h"

template<typename T>
void llama::RandomData::generateRandomData(std::vector<T> *targetVector, int count) {
    unsigned seed = static_cast<unsigned>(time(NULL));
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(5.0, 2.0);

    for (int i = 0; i < count; i++) {
        targetVector->push_back(distribution(generator));
    }
}

template<>
void llama::RandomData::generateRandomData<int>(std::vector<int> *targetVector, int count) {
    unsigned seed = static_cast<unsigned>(time(NULL));
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(10.0, 4.0);

    for (int i = 0; i < count; i++) {
        targetVector->push_back(distribution(generator));
    }
}

template<>
void llama::RandomData::generateRandomData<bool>(std::vector<bool> *targetVector, int count) {
    unsigned seed = static_cast<unsigned>(time(NULL));
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(5.0, 2.0);

    for (int i = 0; i < count; i++) {
        targetVector->push_back(distribution(generator) > 5.0 ? true:false);
    }
}

template<>
void llama::RandomData::generateRandomData<double>(std::vector<double> *targetVector, int count) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(5.0, 2.0);

    for (int i = 0; i < count; i++) {
        targetVector->push_back(distribution(generator));
    }
}
