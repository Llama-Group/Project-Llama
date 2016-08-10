
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

#include "Utility/DataGenerator.h"

#include <vector>
#include <random>
#include <string>

template<>
void llama::RandomData::generateRandomData<int>(std::vector<int> *targetVector, int count) {
    std::random_device rd_int;
    std::mt19937 re_int(rd_int());
    std::uniform_int_distribution<int> ui(1, 100);

    for (int i = 0; i < count; i++) {
        targetVector->push_back(ui(re_int));
    }
}

template<>
void llama::RandomData::generateRandomData<double>(std::vector<double> *targetVector, int count) {
    std::random_device rd_double;
    std::mt19937 re_double(rd_double());
    std::uniform_real_distribution<double> ud(1, 100);

    for (int i = 0; i < count; i++) {
        targetVector->push_back(ud(re_double));
    }
}

template<>
void llama::RandomData::generateRandomData<std::string>(std::vector<std::string> *targetVector, int count) {
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < count; i++) {
        std::string generateStr;
        std::random_device rd_string;
        std::mt19937 re_string(rd_string());
        std::uniform_int_distribution<int> us(1, 10);

        for (int i = 0; i < us(re_string); i++) {
            std::random_device rd_string_index;
            std::mt19937 re_string_index(rd_string_index());
            std::uniform_int_distribution<int> us_index(0, 51);
            generateStr += alpha[us_index(re_string_index)];
            }

        targetVector->push_back(generateStr);
        }
}
