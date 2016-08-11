
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

#include <vector>
#include <iostream>
#include <string>

#include "Utility/DataGenerator.h"

int main(int argc, const char * argv[]) {
    std::vector<int> ar, ac;
    std::vector<double> br, bc;
    std::vector<std::string> cr, cc;
    llama::RandomData mRandomData = llama::RandomData();
    llama::ContinuousData mContinuousData = llama::ContinuousData();
    int counter = 10;
    bool reverse = true;

    mRandomData.generateRandomData(&ar, counter);

    for (const auto &n : ar) {
        std::cout << n << '\n';
    }

    std::cout << "==========" << '\n';

    mRandomData.generateRandomData(&br, counter);

    for (const auto &n : br) {
        std::cout << n << '\n';
    }

    std::cout << "==========" << '\n';

    mRandomData.generateRandomData(&cr, counter);

    for (const auto &n : cr) {
        std::cout << n << '\n';
    }

    std::cout << "==========" << '\n';

    mContinuousData.generateContinuousData(&ac, counter, reverse);

    for (const auto &n : ac) {
        std::cout << n << '\n';
    }

    std::cout << "==========" << '\n';

    mContinuousData.generateContinuousData(&bc, counter, reverse);

    for (const auto &n : bc) {
        std::cout << n << '\n';
    }

    std::cout << "==========" << '\n';

    mContinuousData.generateContinuousData(&cc, counter, reverse);

    for (const auto &n : cc) {
        std::cout << n << '\n';
    }
}
