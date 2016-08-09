
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License,Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at:
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing,software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#ifndef LLAMA_CPP_SRC_SORT_BRUTEFORCESORT_H_
#define LLAMA_CPP_SRC_SORT_BRUTEFORCESORT_H_

#include <vector>
#include <algorithm>

#include "Sort.h"

namespace llama {
template<class T>
class BruteForceSort : public Sort<T> {
 public:
    BruteForceSort() {}
    explicit BruteForceSort(std::vector<T> *inputArray) { this->performSort(inputArray); }

    void doSort(std::vector<SortObject<T>> *reformedArray) override {
        std::vector<SortObject<T>> resultArray(reformedArray->size(), SortObject<T>());
        for (int i = 0; i < reformedArray->size(); ++i) {
            int index = 0;
            for (int j = 0; j < reformedArray->size(); ++j) {
                if (reformedArray->at(i) >= reformedArray->at(j)) {
                    index++;
                }
            }
            index--;
            while (!resultArray[index].na) {
                index--;
            }
            resultArray[index] = reformedArray->at(i);
        }
        std::copy(resultArray.begin(), resultArray.end(), reformedArray->begin());
    }
};
}  // namespace llama

#endif  // LLAMA_CPP_SRC_SORT_BRUTEFORCESORT_H_
