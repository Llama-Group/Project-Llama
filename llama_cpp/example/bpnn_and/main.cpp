
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

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

using llama::NeuralNetwork;

int main(int argc, const char * argv[]) {
    vector<int> layers = {2, 3, 1};

    NeuralNetwork nn = NeuralNetwork(layers);

    cout << "Before train:\n";
    cout << nn.feed({1, 1})[0] << '\n';
    cout << nn.feed({1, 0})[0] << '\n';
    cout << nn.feed({0, 1})[0] << '\n';
    cout << nn.feed({0, 0})[0] << '\n';
    
    for (int i = 0; i < 10000; i++) {
        nn.train({1, 1}, {1});
        nn.train({1, 0}, {0});
        nn.train({0, 1}, {0});
        nn.train({0, 0}, {0});
    }

    cout << "After train:\n";
    cout << nn.feed({1, 1})[0] << '\n';
    cout << nn.feed({1, 0})[0] << '\n';
    cout << nn.feed({0, 1})[0] << '\n';
    cout << nn.feed({0, 0})[0] << '\n';

    return 0;
}
