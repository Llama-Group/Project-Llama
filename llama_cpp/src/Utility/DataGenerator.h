
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
#include <iterator>
#include <limits>
#include <vector>
#include <random>
#include <stdexcept>
#include <string>
#include <type_traits>

#ifndef DATA_GENERATOR_DEFAULT_COUNT
    #define DATA_GENERATOR_DEFAULT_COUNT 10
#elif(DATA_GENERATOR_DEFAULT_COUNT <= 0)
    #define DATA_GENERATOR_DEFAULT_COUNT 10
#endif

#ifndef DATA_GENERATOR_DEFAULT_STRING_MAX_LENGTH
    #define DATA_GENERATOR_DEFAULT_STRING_MAX_LENGTH 20
#elif(DATA_GENERATOR_DEFAULT_STRING_MAX_LENGTH <= 0)
    #define DATA_GENERATOR_DEFAULT_STRING_MAX_LENGTH 20
#endif

#define TYPE_INTEGRAL typename std::enable_if<std::is_integral<T>::value, T>::type
#define TYPE_FLOATING_POINT typename std::enable_if<std::is_floating_point<T>::value, T>::type

typedef enum cases {LE, GE, LT, GT, EQ, NE, RD} Cases;

namespace llama {
class DataGenerator {
 public:
    DataGenerator() {}

    /**
     *  @brief Generate random integral numbers
     */
    template<typename T>
    static void generateRandomData(std::vector<T> *targetVector,
                                   int count = DATA_GENERATOR_DEFAULT_COUNT,
                                   TYPE_INTEGRAL* = 0) {
        T typeMin = std::numeric_limits<T>::min();
        T typeMax = std::numeric_limits<T>::max();
        std::random_device arithmeticRandomDevice;
        std::mt19937 arithmeticRandomEngine(arithmeticRandomDevice());
        std::uniform_int_distribution<T> uniformArithmeticDistribution(typeMin, typeMax);

        for (int i = 0; i < count; i++) {
            targetVector->push_back(uniformArithmeticDistribution(arithmeticRandomEngine));
        }
    }

    /**
     *  @brief Generate random floating point numbers
     */
    template<typename T>
    static void generateRandomData(std::vector<T> *targetVector,
                                   int count = DATA_GENERATOR_DEFAULT_COUNT,
                                   TYPE_FLOATING_POINT* = 0) {
        T typeMin = std::numeric_limits<T>::min();
        T typeMax = std::numeric_limits<T>::max();
        std::random_device arithmeticRandomDevice;
        std::mt19937 arithmeticRandomEngine(arithmeticRandomDevice());
        std::uniform_real_distribution<T> uniformArithmeticDistribution(typeMin, typeMax);

        for (int i = 0; i < count; i++) {
            targetVector->push_back(uniformArithmeticDistribution(arithmeticRandomEngine));
        }
    }

    /**
     *  @brief Generate random bool
     */
    static void generateRandomData(std::vector<bool> *targetVector, int count = DATA_GENERATOR_DEFAULT_COUNT) {
        for (int i = 0; i < count; i++) {
            targetVector->push_back(static_cast<bool>(generateRandomDataFromRange<int>(0, 1)));
        }
    }

    /**
     *  @brief Generate random std::string data
     */
    static void generateRandomData(std::vector<std::string> *targetVector, int count = DATA_GENERATOR_DEFAULT_COUNT);

    /**
     *  @brief Generate random data for given set
     */
    template <typename _RandomAccessIterator>
    static void generateRandomDataFromSet(_RandomAccessIterator __first,
                                          _RandomAccessIterator __last,
                                          std::vector<
                                            typename std::iterator_traits<_RandomAccessIterator>::value_type
                                          > *targetVector,
                                          int count) {
        typedef typename std::iterator_traits<_RandomAccessIterator>::difference_type difference_type;
        difference_type length = std::distance(__first, __last);

        std::random_device intRandomDevice;
        std::mt19937 intRandomEngine(intRandomDevice());
        std::uniform_int_distribution<int> uniformIntDistribution(0, static_cast<int>(length - 1));

        for (int i = 0; i < count; i++) {
            targetVector->push_back(*(__first + uniformIntDistribution(intRandomEngine)));
        }
    }

    /**
     *  @brief Generate random std::string with allowed characters in a single std::string
     */
    static void generateRandomDataFromSet(const std::string& set, std::vector<std::string> *targetVector, int count);

    /**
     *  @brief Generate continuous integral number
     */
    template<typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    static void generateContinuousData(std::vector<T> *targetVector,
                                       T start = 0,
                                       size_t step = 1,
                                       int count = DATA_GENERATOR_DEFAULT_COUNT,
                                       bool reverse = false) {
        if (!reverse) {
            for (T i = start; i < start + (step * count); i += step) {
                targetVector->push_back(i);
            }
        } else {
            for (T i = start + (step * (count - 1)); i >= start; i -= step) {
                targetVector->push_back(i);
            }
        }
    }

    /**
     *  @brief Generate continuous floating point number
     */
    template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
    static void generateContinuousData(std::vector<T> *targetVector,
                                       T start = 0.0,
                                       T step = 0.1,
                                       int count = DATA_GENERATOR_DEFAULT_COUNT,
                                       bool reverse = false) {
        if (!reverse) {
            for (T i = start; i < start + (step * count); i += step) {
                targetVector->push_back(i);
            }
        } else {
            for (T i = start + (step * (count - 1)); i >= start; i -= step) {
                targetVector->push_back(i);
            }
        }
    }

    /**
     *  @brief Generate random std::string in alphabet order
     */
    static void generateContinuousData(std::vector<std::string> *targetVector,
                                       int count = DATA_GENERATOR_DEFAULT_COUNT,
                                       bool reverse = false);

    /**
     *  @brief Generate single datum (arithmetic, aka, integer number and floating point number)
     */
    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    static T generateSingleDatum(const T& givenData = T(), Cases switcher = RD) {
        switch (switcher) {
            case RD: {
                T x = DataGenerator::generateRandomDataFromRange<T>(std::numeric_limits<T>::min(),
                                                                    std::numeric_limits<T>::max());
                return x;
            }
            case LE: {
                return DataGenerator::generateRandomDataFromRange<T>
                   (std::numeric_limits<T>::min(), givenData);
            }
            case GE: {
                return DataGenerator::generateRandomDataFromRange<T>
                   (givenData, std::numeric_limits<T>::max());
            }
            case LT: {
                if (givenData == std::numeric_limits<T>::min()) {
                    throw std::invalid_argument("The given value is the minimum of the specified type.");
                }
                return DataGenerator::generateRandomDataFromRange<T>
                   (std::numeric_limits<T>::min(), givenData - std::numeric_limits<T>::denorm_min());
            }
            case GT: {
                if (givenData == std::numeric_limits<T>::max()) {
                    throw std::invalid_argument("The given value is the maximum of the specified type.");
                }
                return DataGenerator::generateRandomDataFromRange<T>
                   (givenData + std::numeric_limits<T>::denorm_min(), std::numeric_limits<T>::max());
            }
            case EQ: {
                return givenData;
            }
            case NE: {
                T temp;
                do {
                    temp = DataGenerator::generateRandomDataFromRange<T>(std::numeric_limits<T>::min(),
                                                                         std::numeric_limits<T>::max());
                } while (temp == givenData);
                return temp;
            }
            default: {
                throw std::invalid_argument("Unrecognised arguement.");
            }
        }
    }

    /**
     *  @brief Generate single std::string
     */
    static std::string generateSingleDatum(const std::string& givenData = "", Cases = RD);

    /**
     *  @brief Generate single datum from a given range (arithmetic, aka, integer number and floating point number)
     */
    template<typename T>
    static T generateRandomDataFromRange(T min, T max,
                                         TYPE_INTEGRAL* = 0) {
        std::random_device randomDevice;
        std::mt19937 randomEngine(randomDevice());

        std::uniform_int_distribution<T> uniformDistribution(min, max);
        return uniformDistribution(randomEngine);
    }

    template<typename T>
    static T generateRandomDataFromRange(T min, T max,
                                         TYPE_FLOATING_POINT* = 0) {
        std::random_device randomDevice;
        std::mt19937 randomEngine(randomDevice());

        std::uniform_real_distribution<T> uniformDistribution(min, max);
        return uniformDistribution(randomEngine);
    }

    static std::string generateSingleString();
};
}  // namespace llama

#endif  // LLAMA_CPP_SRC_UTILITY_DATAGENERATOR_H_
