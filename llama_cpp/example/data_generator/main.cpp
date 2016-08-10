
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

#include <Utility/DataGenerator.h>

#include <vector>
#include <iostream>
#include <string>

int main(int argc, const char * argv[]) {
    std::vector<int> a;
    std::vector<double> b;
    std::vector<std::string> c;
    llama::RandomData mRandomData = llama::RandomData();
    int ct = 10;

    mRandomData.generateRandomData(&a, ct);

    for (const auto &n : a) {
        std::cout << n << std::endl;
    }

    std::cout << "==========" << std::endl;

    mRandomData.generateRandomData(&b, ct);

    for (const auto &n : b) {
        std::cout << n << std::endl;
    }

    std::cout << "==========" << std::endl;

    mRandomData.generateRandomData(&c, ct);

    for (const auto &n : c) {
        std::cout << n << std::endl;
    }
}
