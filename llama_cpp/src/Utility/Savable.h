
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

#ifndef LLAMA_CPP_SRC_UTILITY_SAVABLE_H_
#define LLAMA_CPP_SRC_UTILITY_SAVABLE_H_

#include <fstream>
#include <iostream>
#include <string>

namespace llama {

class Savable {
 public:
    Savable() {}

    int testData1;
    bool testData2;
    float testData3;


    int saveToFile(std::string fileName = "default.dat");

    int loadFromFile(std::string fileName = "default.dat");
};
}  // namespace llama

#endif  // LLAMA_CPP_SRC_UTILITY_SAVABLE_H_
