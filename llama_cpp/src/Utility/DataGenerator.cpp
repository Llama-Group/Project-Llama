
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

#include <stdexcept>
#include <string>
#include <vector>

using llama::DataGenerator;

void DataGenerator::generateRandomData(std::vector<std::string> *targetVector, int count) {
    static std::string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "§1234567890-=[]';\\,./`±!@£$^&*()_+{}:\"|<>?~";
    DataGenerator::generateRandomDataFromSet(alpha, targetVector, count);
}

void DataGenerator::generateRandomDataFromSet(const std::string& set,
                                              std::vector<std::string> *targetVector,
                                              int count) {
    for (int i = 0; i < count; i++) {
        std::string generateRandomString;
        std::random_device stringRandomDevice;
        std::mt19937 stringRandomEngine(stringRandomDevice());
        std::uniform_int_distribution<int> uniformStringDistribution(1, DATA_GENERATOR_DEFAULT_STRING_MAX_LENGTH);

        for (int i = 0; i < uniformStringDistribution(stringRandomEngine); i++) {
            std::random_device stringIndexRandomDevice;
            std::mt19937 stringIndexRandomEngine(stringIndexRandomDevice());
            std::uniform_int_distribution<int> uniformIndexStringDistribution(0, static_cast<int>(set.size() - 1));
            generateRandomString += set[uniformIndexStringDistribution(stringIndexRandomEngine)];
        }

        targetVector->push_back(generateRandomString);
    }
}

void DataGenerator::generateContinuousData(std::vector<std::string> *targetVector, int count, bool reverse) {
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

std::string DataGenerator::generateSingleString() {
    static std::string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "§1234567890-=[]';\\,./`±!@£$^&*()_+{}:\"|<>?~";

    std::string generateRandomString;
    std::random_device stringRandomDevice;
    std::mt19937 stringRandomEngine(stringRandomDevice());
    std::uniform_int_distribution<int> uniformStringDistribution(1, DATA_GENERATOR_DEFAULT_STRING_MAX_LENGTH);

    for (int i = 0; i < uniformStringDistribution(stringRandomEngine); i++) {
        std::random_device stringIndexRandomDevice;
        std::mt19937 stringIndexRandomEngine(stringIndexRandomDevice());
        std::uniform_int_distribution<int> uniformIndexStringDistribution(0, static_cast<int>(alpha.size() - 1));
        generateRandomString += alpha[uniformIndexStringDistribution(stringIndexRandomEngine)];
    }
    return generateRandomString;
}

std::string DataGenerator::generateSingleDatum(const std::string& givenData, Cases switcher) {
    std::string temp;
    switch (switcher) {
        case RD: {
            return DataGenerator::generateSingleString();
        }

        case LE: {
            do {
                temp = DataGenerator::generateSingleString();
            } while (temp.compare(givenData) <= 0);
            return temp;
        }

        case GE: {
            do {
                temp = DataGenerator::generateSingleString();
            } while (temp.compare(givenData) >= 0);
            return temp;
        }

        case LT: {
            do {
                temp = DataGenerator::generateSingleString();
            } while (temp.compare(givenData) < 0);
            return temp;
        }

        case GT: {
            do {
                temp = DataGenerator::generateSingleString();
            } while (temp.compare(givenData) > 0);
            return temp;
        }

        case EQ: {
            return givenData;
        }

        case NE: {
            do {
                temp = DataGenerator::generateSingleString();
            } while (temp.compare(givenData) == 0);
            return temp;
        }

        default: {
            throw std::invalid_argument("Unrecognised arguement.");
        }
    }
}
