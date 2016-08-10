
//
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless requniformIntDistributionred by applicable law or agreed to in writing, software
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
    std::random_device intRandomDevice;
    std::mt19937 intRandomEngine(intRandomDevice());
    std::uniform_int_distribution<int> uniformIntDistribution(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    for (int i = 0; i < count; i++) {
        targetVector->push_back(uniformIntDistribution(intRandomEngine));
    }
}

template<>
void llama::RandomData::generateRandomData<double>(std::vector<double> *targetVector, int count) {
    std::random_device doubleRandomDevice;
    std::mt19937 doubleRandomEngine(doubleRandomDevice());
    std::uniform_real_distribution<double> uniformDoubleDistribution(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());

    for (int i = 0; i < count; i++) {
        targetVector->push_back(uniformDoubleDistribution(doubleRandomEngine));
    }
}

template<>
void llama::RandomData::generateRandomData<std::string>(std::vector<std::string> *targetVector, int count) {
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ§1234567890-=[]\';\\,./`±!@£$^&*()_+{}:\"|<>?~";

    for (int i = 0; i < count; i++) {
        std::string generateString;
        std::random_device stringRandomDevice;
        std::mt19937 stringRandomEngine(stringRandomDevice());
        std::uniform_int_distribution<int> uniformStringDistribution(1, generateString.max_size());

        for (int i = 0; i < uniformStringDistribution(stringRandomEngine); i++) {
            std::random_device stringIndexRandomDevice;
            std::mt19937 stringIndexRandomEngine(stringIndexRandomDevice());
            std::uniform_int_distribution<int> uniformIndexStringDistribution(0, sizeof(alpha)-1);
            generateString += alpha[uniformIndexStringDistribution(stringIndexRandomEngine)];
        }

        targetVector->push_back(generateString);
        }
}
