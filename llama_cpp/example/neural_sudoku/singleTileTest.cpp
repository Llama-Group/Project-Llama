
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

#include <ML/NeuralNetwork.h>

#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>

using std::cout;
using std::vector;

using llama::NeuralNetwork;

int main() {
/*
    auto mapResult = [](vector<double> &v) {
        if (v.size() < 2) {
            throw std::invalid_argument("Vector size must larger than 1.");
        } else if (v[0] > 1 || v[1] > 1) {
            std::for_each(v.begin(), v.end(), [](double &a) {
                a *= 0.1; });
        } else {
            std::for_each(v.begin(), v.end(), [](double &a) {
                a *= 10; });
        }};
 */
    
    NeuralNetwork nn = NeuralNetwork({2, 7, 2});

    for (int i = 0; i < 20000; i++) {
        nn.train({0, 2}, {0.1, 0.2});
        nn.train({2, 0}, {0.2, 0.1});
        nn.train({0, 1}, {0.2, 0.1});
        nn.train({1, 0}, {0.1, 0.2});
        nn.train({1, 2}, {0.1, 0.2});
        nn.train({2, 1}, {0.2, 0.1});
        nn.train({0, 0}, {0.1, 0.2});
        nn.train({0, 0}, {0.2, 0.1});
    }

    vector<double> outputs = nn.feed({0, 0});
    // mapResult(outputs);
    cout << outputs[0] * 10 << ", "
         << outputs[1] * 10 << '\n';

    return 0;
}
