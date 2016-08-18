
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

using llama::DataGenerator;

template<>
int DataGenerator::generateRandomDataFromRange<int>(int min, int max) {
    std::random_device intRandomDevice;
    std::mt19937 intRandomEngine(intRandomDevice());
    std::uniform_int_distribution<int> uniformIntDistribution(min, max);
    return uniformIntDistribution(intRandomEngine);
}

template<>
double DataGenerator::generateRandomDataFromRange<double>(double min, double max) {
    std::random_device doubleRandomDevice;
    std::mt19937 doubleRandomEngine(doubleRandomDevice());
    std::uniform_real_distribution<double> uniformDoubleDistribution(min, max);
    return uniformDoubleDistribution(doubleRandomEngine);
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

template<>
void DataGenerator::generateRandomData<int, int>(std::vector<int> *targetVector, int min, int max, int count) {

    for (int i = 0; i < count; i++) {
        targetVector->push_back(generateRandomDataFromRange(min, max));
    }
}

template<>
void DataGenerator::generateRandomData<double, double>(std::vector<double> *targetVector, double min, double max, int count) {

    for (int i = 0; i < count; i++) {
        targetVector->push_back(generateRandomDataFromRange(min, max));
    }
}

template<>
void DataGenerator::generateRandomData<std::string, int>(std::vector<std::string> *targetVector,
                                        int min, int max, int count) {
    generateRandomDataFromSet(targetVector, count, min, max);
    
}

void DataGenerator::generateRandomDataFromSet(std::vector<std::string> *targetVector,
                                              int count,
                                              int min,
                                              int max) {
    for (int i = 0; i < count; i++) {
        std::string generateRandomString;
        std::random_device stringRandomDevice;
        std::mt19937 stringRandomEngine(stringRandomDevice());
        std::uniform_int_distribution<int> uniformStringDistribution(1, DATA_GENERATOR_DEFAULT_STRING_MAX_LENGTH);

        for (int i = 0; i < uniformStringDistribution(stringRandomEngine); i++) {
            std::random_device stringIndexRandomDevice;
            std::mt19937 stringIndexRandomEngine(stringIndexRandomDevice());
            std::uniform_int_distribution<int> uniformIndexStringDistribution(min, max);
            generateRandomString += static_cast<char>(uniformIndexStringDistribution(stringIndexRandomEngine));
        }

        targetVector->push_back(generateRandomString);
    }
}

template<>
void DataGenerator::generateContinuousData<int>(std::vector<int> *targetVector, int count, bool reverse) {
    for (int i = 0; i < count; i++) {
        targetVector->push_back(reverse ? (count - i - 1) : i);
    }
}

template<>
void DataGenerator::generateContinuousData<double>(std::vector<double> *targetVector, int count, bool reverse) {
    for (int i = 0; i < count; i++) {
        targetVector->push_back(reverse ? (count - i - 1)/10.0 : i/10.0);
    }
}

template<>
void DataGenerator::generateContinuousData<std::string>
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

template<>
int DataGenerator::generateSingleDatum<int>(int *givenData, Cases switcher) {
    switch (switcher) {
        case RD: {
            return DataGenerator::generateRandomDataFromRange<int>
            (std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        }

        case LE: {
            return DataGenerator::generateRandomDataFromRange<int>(std::numeric_limits<int>::min(), *givenData);
        }

        case GE: {
            return DataGenerator::generateRandomDataFromRange<int>(*givenData, std::numeric_limits<int>::max());
        }

        case LT: {
            if (*givenData == std::numeric_limits<int>::min()) {
                throw std::invalid_argument("The given int is the minimum.");
            }
            return DataGenerator::generateRandomDataFromRange<int>
                (std::numeric_limits<int>::min(), *givenData - 1);
        }

        case GT: {
            if (*givenData == std::numeric_limits<int>::max()) {
                throw std::invalid_argument("The given int is the maximum.");
            }
            return DataGenerator::generateRandomDataFromRange<int>
                (*givenData + 1, std::numeric_limits<int>::max());
        }

        case EQ: {
            return *givenData;
        }

        case NE: {
            int temp;
            do {
                temp = DataGenerator::generateRandomDataFromRange<int>(std::numeric_limits<int>::min(),
                                                                              std::numeric_limits<int>::max());
            } while (temp == *givenData);
            return temp;
        }

        default: {
            throw std::invalid_argument("Unrecognised arguement.");
        }
    }
}

template<>
double DataGenerator::generateSingleDatum<double>(double *givenData, Cases switcher) {
    switch (switcher) {
        case RD: {
            double x = DataGenerator::generateRandomDataFromRange<double>(std::numeric_limits<double>::min(),
                                                                      std::numeric_limits<double>::max());
            return x;
        }

        case LE: {
            return DataGenerator::generateRandomDataFromRange<double>
            (std::numeric_limits<double>::min(), *givenData);
        }

        case GE: {
            return DataGenerator::generateRandomDataFromRange<double>
            (*givenData, std::numeric_limits<double>::max());
        }

        case LT: {
            if (*givenData == std::numeric_limits<double>::min()) {
                throw std::invalid_argument("The given double is the minimum.");
            }
            return DataGenerator::generateRandomDataFromRange<double>
            (std::numeric_limits<double>::min(), *givenData - std::numeric_limits<double>::denorm_min());
        }

        case GT: {
            if (*givenData == std::numeric_limits<double>::max()) {
                throw std::invalid_argument("The given double is the maximum.");
            }
            return DataGenerator::generateRandomDataFromRange<double>
            (*givenData + std::numeric_limits<double>::denorm_min(), std::numeric_limits<double>::max());
        }

        case EQ: {
            return *givenData;
        }

        case NE: {
            double temp;
            do {
                temp = DataGenerator::generateRandomDataFromRange<double>(std::numeric_limits<double>::min(),
                                                                                 std::numeric_limits<double>::max());;
            } while (temp == *givenData);
            return temp;
        }

        default: {
            throw std::invalid_argument("Unrecognised arguement.");
        }
    }
}

template<>
std::string DataGenerator::generateSingleDatum<std::string>(std::string *givenData, Cases switcher) {
    std::string temp;
    switch (switcher) {
        case RD: {
            return DataGenerator::generateSingleString();
        }

        case LE: {
            do {
                temp = DataGenerator::generateSingleString();
            } while (temp.compare(*givenData) <= 0);
            return temp;
        }

        case GE: {
            do {
                temp = DataGenerator::generateSingleString();
            } while (temp.compare(*givenData) >= 0);
            return temp;
        }

        case LT: {
            do {
                temp = DataGenerator::generateSingleString();
            } while (temp.compare(*givenData) < 0);
            return temp;
        }

        case GT: {
            do {
                temp = DataGenerator::generateSingleString();
            } while (temp.compare(*givenData) > 0);
            return temp;
        }

        case EQ: {
            return *givenData;
        }

        case NE: {
            do {
                temp = DataGenerator::generateSingleString();
            } while (temp.compare(*givenData) == 0);
            return temp;
        }

        default: {
            throw std::invalid_argument("Unrecognised arguement.");
        }
    }
}
