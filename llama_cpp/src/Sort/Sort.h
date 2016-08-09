
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

#ifndef LLAMA_CPP_SRC_SORT_SORT_H_
#define LLAMA_CPP_SRC_SORT_SORT_H_

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

// How to add sort algorithm:
// Create a template class "template<class T>" inherit Sort.
// Override void doSort(std::vector<SortObject<T>> *reformedArray).
// Dealing with SortObject.
// Add template specialization to support new type/class.

namespace llama {
// SortObject class, represents each object in the array to sort.
template<class T>
class SortObject {
 public:
    bool na = false;

    explicit SortObject(T inputObject) { obj = inputObject; }
    SortObject() {
        na = true;
    }

    int compare(SortObject<T> comparedObject) const {
        return obj - comparedObject.getObj();
    }

    T getObj() { return obj; }

    bool operator > (const SortObject<T>& s) const { return compare(s) > 0; }
    bool operator < (const SortObject<T>& s) const { return compare(s) < 0; }
    bool operator >= (const SortObject<T>& s) const { return compare(s) >= 0; }
    bool operator <= (const SortObject<T>& s) const { return compare(s) <= 0; }
    bool operator == (const SortObject<T>& s) const { return compare(s) == 0; }

 private:
    T obj;
};

template<>
int SortObject<std::string>::compare(SortObject<std::string> comparedObject) const {
    if (obj.size() > 0 && comparedObject.getObj().size() > 0) {
        return obj[0] - comparedObject.getObj()[0];
    } else if (obj.size() > 0) {
        return 1;
    } else {
        return -1;
    }
}

// Sort class
template<class T>
class Sort {
 public:
    Sort() {}

    void performSort(std::vector<T> *inputArray) {
        std::vector<SortObject<T>> reformedArray;
        for (typename std::vector<T>::iterator it = inputArray->begin(); it != inputArray->end(); ++it) {
            reformedArray.push_back(SortObject<T>(*it));
        }

        doSort(&reformedArray);

        int index = 0;
        for (typename std::vector<T>::iterator it = inputArray->begin(); it != inputArray->end(); ++it) {
            *it = reformedArray.at(index).getObj();
            index++;
        }
    }

 protected:
    virtual void doSort(std::vector<SortObject<T>> *reformedArray) {
        std::cerr << "Abstract function, do not call!" << std::endl;
    }
};
}  // namespace llama

#endif  // LLAMA_CPP_SRC_SORT_SORT_H_
