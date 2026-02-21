
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

#ifndef LLAMA_CPP_SRC_SEARCH_SEARCH_H_
#define LLAMA_CPP_SRC_SEARCH_SEARCH_H_

#include <vector>

namespace llama {
template <class T>
int linearSearch(const std::vector<T>& data, const T& target) {
    for (std::size_t i = 0; i < data.size(); ++i) {
        if (data[i] == target) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

template <class T>
int binarySearch(const std::vector<T>& sortedData, const T& target) {
    int left = 0;
    int right = static_cast<int>(sortedData.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (sortedData[mid] == target) {
            return mid;
        }
        if (sortedData[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}
}  // namespace llama

#endif  // LLAMA_CPP_SRC_SEARCH_SEARCH_H_
