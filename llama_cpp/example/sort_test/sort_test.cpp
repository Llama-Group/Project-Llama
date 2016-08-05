

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

#include "Sort/InsertionSort.h"
#include "Sort/BruteForceSort.h"

#include <string>
#include <vector>

class CustomisedClass {
 public:
    CustomisedClass() {}
    explicit CustomisedClass(int input) {
        this->input = input*10;
    }

    int getInput() const {
        return input;
    }

    operator std::string() const {
        return "CustomisedClass: "+std::to_string(getInput());
    }

 private:
    int input;
};

namespace llama {
template<>
double SortObject<CustomisedClass>::getValue() const {
    return static_cast<double>(obj.getInput());
}
}  // namespace llama

int main() {
    // Easy tests
    // Set the test value.
    std::vector<int> a;
    std::vector<std::string> b;
    std::vector<double> c;
    std::vector<CustomisedClass> d;

    // Original Data
    a = {5, 4, 3, 2, 1};
    b = {"5", "4", "3", "2", "1"};
    c = {5.0, 4.0, 3.0, 2.0, 1.0};
    d = {CustomisedClass(5), CustomisedClass(4),
        CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};

    std::cout << "Original data:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << a[i] << " ";
        std::cout << b[i] << " ";
        std::cout << c[i] << " ";
        std::cout << std::string(d[i]) << " " << std::endl;
    }

    // BruteForceSort
    a = {5, 4, 3, 2, 1};
    b = {"5", "4", "3", "2", "1"};
    c = {5.0, 4.0, 3.0, 2.0, 1.0};
    d = {CustomisedClass(5), CustomisedClass(4),
        CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};

    new llama::BruteForceSort<int>(&a);
    new llama::BruteForceSort<std::string>(&b);
    new llama::BruteForceSort<double>(&c);
    new llama::BruteForceSort<CustomisedClass>(&d);

    std::cout << "BruteForceSort results:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << a[i] << " ";
        std::cout << b[i] << " ";
        std::cout << c[i] << " ";
        std::cout << std::string(d[i]) << " " << std::endl;
    }

    // InsertionSort
    a = {5,4,3,2,1};
    b = {"5", "4", "3", "2", "1"};
    c = {5.0, 4.0, 3.0, 2.0, 1.0};
    d = {CustomisedClass(5), CustomisedClass(4),
        CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};

    new llama::InsertionSort<int>(&a);
    new llama::InsertionSort<std::string>(&b);
    new llama::InsertionSort<double>(&c);
    new llama::InsertionSort<CustomisedClass>(&d);

    std::cout << "InsertionSort results:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << a[i] << " ";
        std::cout << b[i] << " ";
        std::cout << c[i] << " ";
        std::cout << std::string(d[i]) << " " << std::endl;
    }

    return 0;
}
