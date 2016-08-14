
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

template<>
void llama::DataGenerator::generateRandomData<int>(std::vector<int> *targetVector, int count) {
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
void llama::DataGenerator::generateRandomData<double>(std::vector<double> *targetVector, int count) {
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
void llama::DataGenerator::generateRandomData<std::string>(std::vector<std::string> *targetVector, int count) {
    static std::string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "§1234567890-=[]';\\,./`±!@£$^&*()_+{}:\"|<>?~";
    llama::DataGenerator::generateRandomDataFromSet(alpha, targetVector, count);
}

void llama::DataGenerator::generateRandomDataFromSet(const std::string& set,
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

template<>
void llama::DataGenerator::generateContinuousData<int>(std::vector<int> *targetVector, int count, bool reverse) {
    for (int i = 0; i < count; i++) {
        targetVector->push_back(reverse ? (count - i - 1) : i);
    }
}

template<>
void llama::DataGenerator::generateContinuousData<double>(std::vector<double> *targetVector, int count, bool reverse) {
    for (int i = 0; i < count; i++) {
        targetVector->push_back(reverse ? (count - i - 1)/10.0 : i/10.0);
    }
}

template<>
void llama::DataGenerator::generateContinuousData<std::string>
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
int llama::DataGenerator::generateSingleDatum<int>(int *givenData, Cases switcher) {
    int temp;
    int intMin = std::numeric_limits<int>::min();
    int intMax = std::numeric_limits<int>::max();
    std::random_device intRandomDevice;
    std::mt19937 intRandomEngine(intRandomDevice());
    std::uniform_int_distribution<int> uniformIntDistribution(intMin, intMax);

    switch (switcher) {
        case RD: {
            return uniformIntDistribution(intRandomEngine);
        }

        case LE: {
            do {
                temp = uniformIntDistribution(intRandomEngine);
            } while (temp <= *givenData);
            return temp;
        }

        case GE: {
            do {
                temp = uniformIntDistribution(intRandomEngine);
            } while (temp >= *givenData);
            return temp;
        }

        case LT: {
            do {
                temp = uniformIntDistribution(intRandomEngine);
            } while (temp < *givenData);
            return temp;
        }

        case GT: {
            do {
                temp = uniformIntDistribution(intRandomEngine);
            } while (temp > *givenData);
            return temp;
        }

        case EQ: {
            return *givenData;
        }

        case NE: {
            do {
                temp = uniformIntDistribution(intRandomEngine);
            } while (temp == *givenData);
            return temp;
        }
    }
}

template<>
double llama::DataGenerator::generateSingleDatum<double>(double *givenData, Cases switcher) {
    double temp;
    double doubleMin = std::numeric_limits<double>::min();
    double doubleMax = std::numeric_limits<double>::max();
    std::random_device doubleRandomDevice;
    std::mt19937 doubleRandomEngine(doubleRandomDevice());
    std::uniform_real_distribution<double> uniformDoubleDistribution(doubleMin, doubleMax);

    switch (switcher) {
        case RD: {
            return uniformDoubleDistribution(doubleRandomEngine);
        }

        case LE: {
            do {
                temp = uniformDoubleDistribution(doubleRandomEngine);
            } while (temp <= *givenData);
            return temp;
        }

        case GE: {
            do {
                temp = uniformDoubleDistribution(doubleRandomEngine);
            } while (temp >= *givenData);
            return temp;
        }

        case LT: {
            do {
                temp = uniformDoubleDistribution(doubleRandomEngine);
            } while (temp < *givenData);
            return temp;
        }

        case GT: {
            do {
                temp = uniformDoubleDistribution(doubleRandomEngine);
            } while (temp > *givenData);
            return temp;
        }

        case EQ: {
            return *givenData;
        }

        case NE: {
            do {
                temp = uniformDoubleDistribution(doubleRandomEngine);
            } while (temp == *givenData);
            return temp;
        }
    }
}

template<>
std::string llama::DataGenerator::generateSingleDatum<std::string>(std::string *givenData, Cases switcher) {
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "§1234567890-=[]';\\,./`±!@£$^&*()_+{}:\"|<>?~";

    std::string generateRandomString;
    std::random_device stringRandomDevice;
    std::mt19937 stringRandomEngine(stringRandomDevice());
    std::uniform_int_distribution<int> uniformStringDistribution(1, DATA_GENERATOR_DEFAULT_STRING_MAX_LENGTH);

    switch (switcher) {
        case RD: {
            for (int i = 0; i < uniformStringDistribution(stringRandomEngine); i++) {
                std::random_device stringIndexRandomDevice;
                std::mt19937 stringIndexRandomEngine(stringIndexRandomDevice());
                std::uniform_int_distribution<int> uniformIndexStringDistribution(0, sizeof(alpha)-1);
                generateRandomString += alpha[uniformIndexStringDistribution(stringIndexRandomEngine)];
            }
            return generateRandomString;
        }

        case LE: {
            do {
                for (int i = 0; i < uniformStringDistribution(stringRandomEngine); i++) {
                    std::random_device stringIndexRandomDevice;
                    std::mt19937 stringIndexRandomEngine(stringIndexRandomDevice());
                    std::uniform_int_distribution<int> uniformIndexStringDistribution(0, sizeof(alpha)-1);
                    generateRandomString += alpha[uniformIndexStringDistribution(stringIndexRandomEngine)];
                }
            } while (generateRandomString.compare(*givenData) <= 0);
            return generateRandomString;
        }

        case GE: {
            do {
                for (int i = 0; i < uniformStringDistribution(stringRandomEngine); i++) {
                    std::random_device stringIndexRandomDevice;
                    std::mt19937 stringIndexRandomEngine(stringIndexRandomDevice());
                    std::uniform_int_distribution<int> uniformIndexStringDistribution(0, sizeof(alpha)-1);
                    generateRandomString += alpha[uniformIndexStringDistribution(stringIndexRandomEngine)];
                }
            } while (generateRandomString.compare(*givenData) >= 0);
            return generateRandomString;
        }

        case LT: {
            do {
                for (int i = 0; i < uniformStringDistribution(stringRandomEngine); i++) {
                    std::random_device stringIndexRandomDevice;
                    std::mt19937 stringIndexRandomEngine(stringIndexRandomDevice());
                    std::uniform_int_distribution<int> uniformIndexStringDistribution(0, sizeof(alpha)-1);
                    generateRandomString += alpha[uniformIndexStringDistribution(stringIndexRandomEngine)];
                }
            } while (generateRandomString.compare(*givenData) < 0);
            return generateRandomString;
        }

        case GT: {
            do {
                for (int i = 0; i < uniformStringDistribution(stringRandomEngine); i++) {
                    std::random_device stringIndexRandomDevice;
                    std::mt19937 stringIndexRandomEngine(stringIndexRandomDevice());
                    std::uniform_int_distribution<int> uniformIndexStringDistribution(0, sizeof(alpha)-1);
                    generateRandomString += alpha[uniformIndexStringDistribution(stringIndexRandomEngine)];
                }
            } while (generateRandomString.compare(*givenData) > 0);
            return generateRandomString;
        }

        case EQ: {
            return *givenData;
        }

        case NE: {
            do {
                for (int i = 0; i < uniformStringDistribution(stringRandomEngine); i++) {
                    std::random_device stringIndexRandomDevice;
                    std::mt19937 stringIndexRandomEngine(stringIndexRandomDevice());
                    std::uniform_int_distribution<int> uniformIndexStringDistribution(0, sizeof(alpha)-1);
                    generateRandomString += alpha[uniformIndexStringDistribution(stringIndexRandomEngine)];
                }
            } while (generateRandomString.compare(*givenData) == 0);
            return generateRandomString;
        }
    }
}
