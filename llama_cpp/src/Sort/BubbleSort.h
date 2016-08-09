
//
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#ifndef LLAMA_CPP_SRC_SORT_BUBBLESORT_H_
#define LLAMA_CPP_SRC_SORT_BUBBLESORT_H_

#include <algorithm>
#include <vector>

#include "Sort.h"

namespace llama {
template<class T>
class BubbleSort : public Sort<T> {
 public:
    BubbleSort() {}
    explicit BubbleSort(std::vector<T> *inputArray) { this->performSort(inputArray); }

    void doSort(std::vector<SortObject<T>> *reformedArray) override {
        SortObject<T> temp;
        for (int i = 0; i < reformedArray->size()-1; i++) {
            for (int j = 0; j < reformedArray->size()-1-i; j++) {
                if (reformedArray->at(j) > reformedArray->at(j+1))
                // Swap between i+1 and the i
                temp = reformedArray->at(j);
                reformedArray->at(j) = reformedArray->at(j+1);
                reformedArray->at(j+1) = temp;
            }
        }
    }
};
}  //  namespace llama
#endif  // LLAMA_CPP_SRC_SORT_BUBBLESORT_H_
