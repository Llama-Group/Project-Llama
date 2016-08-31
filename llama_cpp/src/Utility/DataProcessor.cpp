
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

#include <Utility/DataProcessor.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

using llama::DataProcessor;

int DataProcessor::readLine(vector<double> *output) {
    if (csvReader.eof()) {
        return 0;
    }

    string line;
    if (!getline(csvReader, line)) {
        // TODO(Bluecocoa): Use llama log.
        std::cerr << "Failed to read line.\n";
        return -1;
    }

    std::istringstream lineStream(line);
    string sElement;
    while (getline(lineStream, sElement, ',')) {
        output->push_back(stod(sElement));
    }

    // TODO(Giolno): Change to some more meaningful number.
    return 1;
}

void DataProcessor::readLines(vector<vector<double>> *outputs) {
    int ret = 1;
    while (ret) {
        vector<double> output;
        ret = readLine(&output);
        outputs->push_back(output);
    }
}

