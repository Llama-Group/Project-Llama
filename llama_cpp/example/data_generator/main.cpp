
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
    int as;
    double bs;
    std::string cs;
    std::vector<int> ar, ac;
    std::vector<double> br, bc;
    std::vector<std::string> cr, cc;

    llama::DataGenerator mRandomData = llama::DataGenerator();
    llama::DataGenerator mContinuousData = llama::DataGenerator();
    llama::DataGenerator mSingleData = llama::DataGenerator();

    mRandomData.generateRandomData(&ar);
    mRandomData.generateRandomData(&br);
    mRandomData.generateRandomData(&cr);
    mContinuousData.generateContinuousData(&ac);
    mContinuousData.generateContinuousData(&bc);
    mContinuousData.generateContinuousData(&cc);
    mSingleData.generateSingleData(&as);
    mSingleData.generateSingleData(&bs);
    mSingleData.generateSingleData(&cs);

    std::cout << "===== Random Int =====" << '\n';
    for (const auto &n : ar) {
        std::cout << n << '\n';
    }

    std::cout << "===== Random Double =====" << '\n';
    for (const auto &n : br) {
        std::cout << n << '\n';
    }

    std::cout << "===== Random String =====" << '\n';
    for (const auto &n : cr) {
        std::cout << n << '\n';
    }

    std::cout << "===== Continuous Int =====" << '\n';
    for (const auto &n : ac) {
        std::cout << n << '\n';
    }

    std::cout << "===== Continuous Double =====" << '\n';
    for (const auto &n : bc) {
        std::cout << n << '\n';
    }

    std::cout << "===== Continuous String =====" << '\n';
    for (const auto &n : cc) {
        std::cout << n << '\n';
    }

    std::cout << "===== Single Int =====" << '\n';
    std::cout << as << '\n';

    std::cout << "===== Single Double =====" << '\n';
    std::cout << bs << '\n';

    std::cout << "===== Single String =====" << '\n';
    std::cout << cs << '\n';
}
