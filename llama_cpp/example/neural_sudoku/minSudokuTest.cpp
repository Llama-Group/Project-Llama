
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
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

using llama::NeuralNetwork;

class DataProcessor {
 public:
    DataProcessor() {}
    ~DataProcessor() {
        csvReader.close();
    }
    explicit DataProcessor(std::string filePath) {
        csvReader.open(filePath);
    }

    int readLine(vector<double> *output);
    void readLines(vector<vector<double>> *outputs);

 private:
    std::ifstream csvReader;
};

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

int main() {
    DataProcessor puzFile("puzzle.csv");
    DataProcessor solFile("solution.csv");

    NeuralNetwork nn({16, 17, 17, 17, 16});

    for (int i = 0; i < 2; i++) {
        vector<double> puz;
        puzFile.readLine(&puz);
        vector<double> sol;
        solFile.readLine(&sol);
        std::for_each(sol.begin(), sol.end(), [](double &d){ d *= 0.1; });
        nn.train(1000, [&]() {
            nn.train(puz, sol);
        });
    }

    vector<double> res = nn.feed({0, 0, 2, 0, 0, 0, 3, 1, 4, 0, 0, 0, 0, 3, 0, 0});
    std::for_each(res.begin(), res.end(), [](double d){ cout << d * 10 << ", "; });
    cout << std::endl;
}
