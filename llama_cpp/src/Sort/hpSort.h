
//
//  Sort.hpp
//  Project Llama
//
//  Created by BlueCocoa on 2016/7/27.
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


#ifndef LLAMA_CPP_SRC_SORT_HPSORT_H_
#define LLAMA_CPP_SRC_SORT_HPSORT_H_

#include <sys/types.h>

#include <cstdint>
#include <type_traits>
#include <utility>
#include <algorithm>

namespace alpaca {
typedef enum : uint32_t {
    BUBBLE_SORT,
    COCKTAIL_SORT,
    INSERTION_SORT,
    SELECTION_SORT,
    SHELL_SORT,
    QUICK_SORT,
} method_t;

template <typename Condition, typename T = void>
using EnableIf = typename std::enable_if<Condition::value, T>::type;

template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
void __bubble_sort(T* && data, ssize_t len)
__attribute__((visibility("hidden")));

template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
void __cocktail_sort(T* && data, ssize_t len)
__attribute__((visibility("hidden")));

template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
void __insertion_sort(T* && data, ssize_t len)
__attribute__((visibility("hidden")));

template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
void __selection_sort(T* && data, ssize_t len)
__attribute__((visibility("hidden")));

template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
void __shell_sort(T* && data, ssize_t len)
__attribute__((visibility("hidden")));

template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
void __quick_sort(T* && data, ssize_t low, ssize_t high)
__attribute__((visibility("hidden")));

template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
void sort(method_t method, T* && data, ssize_t len) {
    switch (len) {
        case 0:
        case 1:
            return;
        case 2:
            if (data[0] > data[1]) {
                T tmp = data[0];
                data[0] = data[1];
                data[1] = tmp;
            }
        default:
            break;
    }
    switch (method) {
        case BUBBLE_SORT:
            __bubble_sort(std::forward<T* &&>(data), len);
            break;
        case COCKTAIL_SORT:
            __cocktail_sort(std::forward<T* &&>(data), len);
            break;
        case INSERTION_SORT:
            __insertion_sort(std::forward<T* &&>(data), len);
            break;
        case SELECTION_SORT:
            __selection_sort(std::forward<T* &&>(data), len);
            break;
        case SHELL_SORT:
            __shell_sort(std::forward<T* &&>(data), len);
            break;
        case QUICK_SORT:
            __quick_sort(std::forward<T* &&>(data), 0, len - 1);
            break;
        default:
            break;
    }
}

template<typename T, typename>
void __bubble_sort(T* && data, ssize_t len) {
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (data[i] > data[j]) {
                T temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
}

template<typename T, typename>
void __cocktail_sort(T* && data, ssize_t len) {
    bool swapped;
    do {
        swapped = false;
        for (ssize_t i = 0; i < len - 2; i++) {
            if (data[i] > data[i + 1]) {
                T temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }

        swapped = false;
        for (ssize_t j = len - 2; j >= 0; j--) {
            if (data[j] > data[j + 1]) {
                T temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                swapped = true;
            }
        }
    } while (swapped);
}

template<typename T, typename>
void __insertion_sort(T* && data, ssize_t len) {
    for (size_t i = 1; i < len; i++) {
        if (data[i - 1] > data[i]) {
            T temp = data[i];
            int64_t j = i;
            while (j > 0 && data[j - 1] > temp) {
                data[j] = data[j - 1];
                j--;
            }
            data[j] = temp;
        }
    }
}

template<typename T, typename>
void __selection_sort(T* && data, ssize_t len) {
    for (size_t i = 0; i < len; i++) {
        T min = data[i];
        size_t min_index = i;
        for (size_t j = i; j < len; j++) {
            if (data[j] < min) {
                min = data[j];
                min_index = j;
            }
        }
        if (min_index != i) {
            T temp = data[i];
            data[i] = data[min_index];
            data[min_index] = temp;
        }
    }
}

template<typename T, typename>
void __shell_sort(T* && data, ssize_t len) {
    ssize_t group, i, j;
    for (group = len / 2; group > 0; group /= 2) {
        for (i = group; i < len; i++) {
            for (j = i - group; j >= 0; j -= group) {
                if (data[j] > data[j + group]) {
                    T temp = data[j];
                    data[j] = data[j + group];
                    data[j + group] = temp;
                }
            }
        }
    }
}

template<typename T, typename>
void __quick_sort(T* && data, ssize_t low, ssize_t high) {
    auto partition = [&](int64_t low_p, int64_t high_p) -> int64_t {
        T pivot = data[low_p];
        while (low_p < high_p) {
            while (low_p < high_p && data[high_p] > pivot) high_p--;
            data[low_p] = data[high_p];
            while (low_p < high_p && data[low_p] <= pivot) low_p++;
            data[high_p] = data[low_p];
        }
        data[low_p] = pivot;
        return low_p;
    };
    size_t loc = 0;
    if (low < high) {
        loc = partition(low, high);
        __quick_sort(std::forward<T* &&>(data), low, loc - 1);
        __quick_sort(std::forward<T* &&>(data), loc + 1, high);
    }
}
}  // namespace alpaca

#endif  // LLAMA_CPP_SRC_SORT_HPSORT_H_
