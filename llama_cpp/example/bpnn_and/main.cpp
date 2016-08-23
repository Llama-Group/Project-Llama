
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

double calcAvgTotalError(NeuralNetwork *nn, double a, double b, double c, double d) {
    return nn->getTotalError({0, 0}, {a}) * 0.25 +
           nn->getTotalError({0, 1}, {b}) * 0.25 +
           nn->getTotalError({1, 0}, {c}) * 0.25 +
           nn->getTotalError({1, 1}, {d});
}

int main(int argc, const char * argv[]) {
    vector<int> layers = {2, 1};

    NeuralNetwork nn = NeuralNetwork(layers);

    double a = 0;
    double b = 0;
    double c = 0;
    double d = 1;

    cout << "Before train:\n";
    cout << nn.feed({0, 0})[0] << '\n';
    cout << nn.feed({0, 1})[0] << '\n';
    cout << nn.feed({1, 0})[0] << '\n';
    cout << nn.feed({1, 1})[0] << '\n';
    cout << "Total error: " << calcAvgTotalError(&nn, a, b, c, d) << '\n';

    for (int i = 0; i < 2000; i++) {
        nn.train({0, 0}, {a});
        nn.train({0, 1}, {b});
        nn.train({1, 0}, {c});
        nn.train({1, 1}, {d});

        std::cout << "Total error: " << calcAvgTotalError(&nn, a, b, c, d) << '\n';
        system("clear");
    }

    cout << "After train:\n";
    cout << nn.feed({0, 0})[0] << '\n';
    cout << nn.feed({0, 1})[0] << '\n';
    cout << nn.feed({1, 0})[0] << '\n';
    cout << nn.feed({1, 1})[0] << '\n';
    cout << "Total error: " << calcAvgTotalError(&nn, a, b, c, d) << '\n';

    cout << "Result:\n";
    cout << "False,  False  ->  " << (nn.feed({0, 0})[0] > 0.5 ? "True" : "False") << '\n';
    cout << "False,  True   ->  " << (nn.feed({0, 1})[0] > 0.5 ? "True" : "False") << '\n';
    cout << "True,   False  ->  " << (nn.feed({1, 0})[0] > 0.5 ? "True" : "False") << '\n';
    cout << "True,   True   ->  " << (nn.feed({1, 1})[0] > 0.5 ? "True" : "False") << '\n';

    return 0;
}
