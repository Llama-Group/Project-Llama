
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

#ifndef LLAMA_CPP_SRC_SEARCH_ITERATIVESEARCH_H_
#define LLAMA_CPP_SRC_SEARCH_ITERATIVESEARCH_H_

#include <Search/Search.h>
#include <vector>

namespace llama {
template <class T>
class IterativeSearch {
 public:
    int linear(const std::vector<T>& data, const T& target) const {
        return linearSearch(data, target);
    }

    int binary(const std::vector<T>& sortedData, const T& target) const {
        return binarySearch(sortedData, target);
    }
};
}  // namespace llama

#endif  // LLAMA_CPP_SRC_SEARCH_ITERATIVESEARCH_H_
