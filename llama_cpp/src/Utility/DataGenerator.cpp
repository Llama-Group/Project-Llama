
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
#include <limits>

template<>
void llama::RandomData::generateRandomData<int>(std::vector<int> *targetVector, int count) {
    int intMin = std::numeric_limits<int>::min();
    int intMax = std::numeric_limits<int>::max();
    std::random_device intRandomDevice;
    std::mt19937 intRandomEngine(intRandomDevice());
    std::uniform_int_distribution<int> uniformIntDistribution(intMin, intMax);

    for (int i = 0; i < count; i++) {
        targetVector->push_back(uniformIntDistribution(intRandomEngine));
    }
}

template<>
void llama::RandomData::generateRandomData<double>(std::vector<double> *targetVector, int count) {
    double doubleMin = std::numeric_limits<double>::min();
    double doubleMax = std::numeric_limits<double>::max();
    std::random_device doubleRandomDevice;
    std::mt19937 doubleRandomEngine(doubleRandomDevice());
    std::uniform_real_distribution<double> uniformDoubleDistribution(doubleMin, doubleMax);

    for (int i = 0; i < count; i++) {
        targetVector->push_back(uniformDoubleDistribution(doubleRandomEngine));
    }
}

template<>
void llama::RandomData::generateRandomData<std::string>(std::vector<std::string> *targetVector, int count) {
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "§1234567890-=[]\';\\,./`±!@£$^&*()_+{}:\"|<>?~";

    for (int i = 0; i < count; i++) {
        std::string generateRandomString;
        std::random_device stringRandomDevice;
        std::mt19937 stringRandomEngine(stringRandomDevice());
        std::uniform_int_distribution<int> uniformStringDistribution(1, 20);

        for (int i = 0; i < uniformStringDistribution(stringRandomEngine); i++) {
            std::random_device stringIndexRandomDevice;
            std::mt19937 stringIndexRandomEngine(stringIndexRandomDevice());
            std::uniform_int_distribution<int> uniformIndexStringDistribution(0, sizeof(alpha)-1);
            generateRandomString += alpha[uniformIndexStringDistribution(stringIndexRandomEngine)];
        }

        targetVector->push_back(generateRandomString);
    }
}

template<>
void llama::ContinuousData::generateContinuousData<int>(std::vector<int> *targetVector, int count, bool reverse) {
    for (int i = 0; i < count; i++) {
        targetVector->push_back(reverse ? (count - i - 1) : i);
    }
}

template<>
void llama::ContinuousData::generateContinuousData<double>(std::vector<double> *targetVector, int count, bool reverse) {
    for (int i = 0; i < count; i++) {
        targetVector->push_back(reverse ? (count - i - 1)/10.0 : i/10.0);
    }
}

template<>
void llama::ContinuousData::generateContinuousData<std::string>
(std::vector<std::string> *targetVector, int count, bool reverse) {
    std::string generateConinuousString;
    std::vector<std::string>::iterator it;

    if (reverse) {
        for (int i = 97; i < count + 97; i++) {
            generateConinuousString += static_cast<char>(i);
            it = targetVector->begin();
            it = targetVector->insert(it, generateConinuousString);
        }
    } else {
        for (int i = 97; i < count + 97; i++) {
            generateConinuousString += static_cast<char>(i);
            targetVector->push_back(generateConinuousString);
        }
    }
}
