
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
#include <string>

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

typedef enum cases {LE, GE, LT, GT, EQ, NE, RD} Cases;

namespace llama {

class DataGenerator {
 public:
    DataGenerator() {}

    template<typename T>
    static void generateRandomData(std::vector<T> *targetVector, int count = DATA_GENERATOR_DEFAULT_COUNT);

    static void generateRandomDataFromSet(const std::string& set, std::vector<std::string> *targetVector, int count);

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

    template<typename T>
    static void generateContinuousData(std::vector<T> *targetVector,
                                       int count = DATA_GENERATOR_DEFAULT_COUNT,
                                       bool reverse = false);

    template<typename T>
    static T generateSingleDatum(T *givenData = NULL, Cases = RD);

    template<typename T>
    static T generateRandomDataFromRange(T min, T max);

    static std::string generateSingleString();
};

}  // namespace llama

#endif  // LLAMA_CPP_SRC_UTILITY_DATAGENERATOR_H_
