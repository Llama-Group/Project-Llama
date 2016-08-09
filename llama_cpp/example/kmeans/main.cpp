
//
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include <ML/kmeans.h>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>
#include <utility>

using std::vector;
using std::copy;
using std::cout;
using std::pair;
using std::ostream_iterator;

int main(int argc, const char * argv[]) {
    vector<double> data;

    for (int i = 0; i < 10; i++) {
        data.emplace_back(233 + random() % 10);
        data.emplace_back(233 - random() % 10);
    }
    for (int i = 0; i < 10; i++) {
        data.emplace_back(2333 + random() % 10);
        data.emplace_back(2333 - random() % 10);
    }
    for (int i = 0; i < 10; i++) {
        data.emplace_back(23333 + random() % 10);
        data.emplace_back(23333 - random() % 10);
    }

    vector<double> result = alpaca::ML::kmeans<double>(3, 2, data,
       [&](const vector<pair<double, uint32_t>>& data) -> double {
        double total = 0, count = 0;

        for_each(data.cbegin(), data.cend(), [&total, &count](const pair<double, uint32_t>& point){
            total += point.first;
            count += point.second;
        });
        return total/count;
    }, [&](const double& first, const double& second) -> double {
        double dis = first - second;
        return dis < 0 ? -dis : dis;
    });

    copy(result.cbegin(), result.cend(), ostream_iterator<double>(cout, " "));
    return 0;
}
