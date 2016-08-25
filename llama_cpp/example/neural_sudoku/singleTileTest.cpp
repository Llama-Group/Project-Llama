
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
    NeuralNetwork nn = NeuralNetwork({4, 5, 4});

    auto toResult = [](vector<double> v) { std::for_each(v.begin(), v.end(), [](double a){ return a * 0.1; }); };

    vector<double> tileBox = {1, 2, 3, 4};
    vector<double> result(tileBox);
    toResult(result);

    for (int i = 0; i < 10000; i++) {
        nn.train(tileBox, result);
    }

    vector<double> outputs = nn.feed({1, 2, 3, 4});
    cout << outputs[0] << ' '
         << outputs[1] << ' '
         << outputs[2] << ' '
         << outputs[3] << '\n';

    return 0;
}
