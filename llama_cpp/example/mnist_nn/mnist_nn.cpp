
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

#include "MNISTReader.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

int main() {
    MNISTReader rd;

    llama::NeuralNetwork nn({784, 300, 100, 10});

    auto *trainImageBundle = new vector<vector<double>>();
    auto *trainClassBundle = new vector<vector<double>>();
    auto *testImageBundle = new vector<vector<double>>();
    auto *testClassBundle = new vector<uint8_t>();

    rd.readImageData("train-images.idx3-ubyte", trainImageBundle);
    rd.readClassData("train-labels.idx1-ubyte", trainClassBundle);

    auto itImage = trainImageBundle->begin();
    auto itClass = trainClassBundle->begin();
    for (; itImage < trainImageBundle->end(); itImage++, itClass++) {
        nn.train(*itImage, *itClass);
        if (std::distance(trainImageBundle->begin(), itImage) % 600 == 0) {
            system("clear");
            cout << std::distance(trainImageBundle->begin(), itImage) / 600 << "%\n";
        }
    }
    system("clear");
    cout << "100%\nDone.\n";

    delete trainImageBundle;
    delete trainClassBundle;

    // Get accuracy.
    rd.readImageData("t10k-images.idx3-ubyte", testImageBundle);
    rd.readClassData("t10k-labels.idx1-ubyte", testClassBundle);

    double accuracy = 0.0;

    auto itImageTest = testImageBundle->begin();
    auto itClassTest = testClassBundle->begin();
    for (; itImageTest < testImageBundle->end(); itImageTest++, itClassTest++) {
        auto res = nn.feed(*itImageTest);
        int ans = -1;
        double maxVal = -1.0;
        for (auto it = res.begin(); it < res.end(); it++) {
            if (*it > maxVal) {
                maxVal = *it;
                ans = std::distance(res.begin(), it);
            }
        }
        if (ans == *itClassTest) {
            accuracy++;
        }
    }

    accuracy /= 100;
    cout << "Accuracy: " << accuracy << "%" << '\n';

    // Sample output.
    int chosenNum = 2;
    int lineCount = 0;
    std::for_each(testImageBundle->at(chosenNum).begin(),
                  testImageBundle->at(chosenNum).end(),
                  [&](double d) {
                      if (lineCount >= 28) {
                          cout << '\n';
                          lineCount = 0;
                      }
                      cout << (d > 0.5 ? 'o' : ' ') << ' ';
                      lineCount++;});

    cout << '\n';
    auto res = nn.feed(testImageBundle->at(chosenNum));
    int ans = -1;
    double maxVal = -1.0;
    for (auto it = res.begin(); it < res.end(); it++) {
        if (*it > maxVal) {
            maxVal = *it;
            ans = std::distance(res.begin(), it);
        }
    }
    cout << "Result: " << ans;
    cout << '\n' << "Expected: " << static_cast<int>(testClassBundle->at(chosenNum)) << '\n';

    delete testImageBundle;
    delete testClassBundle;

    return 0;
}

