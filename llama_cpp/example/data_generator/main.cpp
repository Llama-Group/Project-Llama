
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
    int as = 100;
    double bs = 7.11836e+307;
    std::string cs = "asd";
    std::vector<int> ar, ac;
    std::vector<double> br, bc;
    std::vector<std::string> cr, cc;

    llama::DataGenerator mRandomData = llama::DataGenerator();
    llama::DataGenerator mContinuousData = llama::DataGenerator();
    llama::DataGenerator mSingleDatum = llama::DataGenerator();

    mRandomData.generateRandomData(&ar);
    mRandomData.generateRandomData(&br);
    mRandomData.generateRandomData(&cr);
    mContinuousData.generateContinuousData(&ac);
    mContinuousData.generateContinuousData(&bc);
    mContinuousData.generateContinuousData(&cc);
    mSingleDatum.generateSingleDatum(&as);
    mSingleDatum.generateSingleDatum(&bs);
    mSingleDatum.generateSingleDatum(&cs);

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
    std::cout << mSingleDatum.generateSingleDatum(&as) << '\n';

    std::cout << "===== Single Double =====" << '\n';
    std::cout << mSingleDatum.generateSingleDatum(&bs, LT) << '\n';

    std::cout << "===== Single String =====" << '\n';
    std::cout << mSingleDatum.generateSingleDatum(&cs, EQ) << '\n';
}
