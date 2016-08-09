
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

#ifndef LLAMA_CPP_SRC_SORT_INSERTIONSORT_H_
#define LLAMA_CPP_SRC_SORT_INSERTIONSORT_H_

#include <vector>

#include "Sort.h"

namespace llama {
template<class T>
class InsertionSort : public Sort<T> {
 public:
    InsertionSort() {}
    explicit InsertionSort(std::vector<T> *inputArray) { this->performSort(inputArray); }

    void doSort(std::vector<SortObject<T>> *reformedArray) override {
        for (int i = 1; i < reformedArray->size(); i++) {
            // Set key value.
            SortObject<T> key = reformedArray->at(i);
            // Set temp value.
            int index = i;
            // While the index > 0, comparing the (index-1) with the key
            // until we find a (index-1) which is smaller than key, end
            // the loop.
            while (index > 0 && reformedArray->at(index-1) > key) {
                reformedArray->at(index) = reformedArray->at(index-1);
                // Move towards the head.
                index--;
            }
            reformedArray->at(index) = key;
        }
    }
};
}  // namespace llama

#endif  // LLAMA_CPP_SRC_SORT_INSERTIONSORT_H_
