
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

#ifndef LLAMA_CPP_EXAMPLE_MNIST_NN_MNISTREADER_H_
#define LLAMA_CPP_EXAMPLE_MNIST_NN_MNISTREADER_H_

#include <algorithm>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

#define IDX3_MAGIC 0x00000803
#define IDX1_MAGIC 0x00000801

typedef enum FileType {IDX3, IDX1} FileType;

class MNISTReader {
 public:
    MNISTReader() {}

    template<typename T>
    void readImageData(std::string filePath,
                       T *imageBundle) {
        setup(filePath);
        getImages(imageBundle);
    }

    template<typename T>
    void readClassData(std::string filePath, T *classBundle) {
        setup(filePath);
        getClasses(classBundle);
    }

 private:
    std::ifstream fileReader;

    FileType currentType;
    uint32_t unitCount;
    uint32_t rowCount;
    uint32_t columnCount;

    uint32_t readInt() {
        uint8_t readChar[4];
        fileReader.read(reinterpret_cast<char *>(readChar), sizeof(uint32_t));
        uint32_t retVal = (readChar[0] << 24) | (readChar[1] << 16) | (readChar[2] << 8) | readChar[3];
        return retVal;
    }

    void setup(std::string filePath) {
        if (fileReader.is_open()) {
            // TODO(anyone): throw an exception. File already open.
            return;
        }

        fileReader.open(filePath.c_str(), std::fstream::binary | std::fstream::internal);
        // TODO(anyone): add file successfully opened check here.

        // Read magic.
        uint32_t magic;
        magic = readInt();

        switch (magic) {
            case IDX3_MAGIC:
                currentType = IDX3;
                unitCount = readInt();
                rowCount = readInt();
                columnCount = readInt();
                break;
            case IDX1_MAGIC:
                currentType = IDX1;
                unitCount = readInt();
                break;
            default:
                // TODO(anyone): throw an exception.
                break;
        }
    }

    void getImages(std::vector<std::vector<std::vector<uint8_t>>> *imageBundle) {
        imageBundle->push_back({});
        for (int currentUnit = 0; currentUnit < unitCount; currentUnit++) {
            imageBundle->at(currentUnit).push_back({});
            for (int currentRow = 0; currentRow < rowCount; currentRow++) {
                imageBundle->at(currentUnit)[currentRow].push_back({});
                for (int currentColumn = 0; currentColumn < columnCount; currentColumn++) {
                    uint8_t readByte;
                    fileReader.read(reinterpret_cast<char *>(&readByte), sizeof(uint8_t));
                    imageBundle->at(currentUnit)[currentRow].push_back(readByte);
                }
            }
        }
        fileReader.close();
    }

    void getImages(std::vector<std::vector<double>> *imageBundle) {
        for (int currentUnit = 0; currentUnit < unitCount; currentUnit++) {
            const int kOneDArraySize = rowCount * columnCount;
            uint8_t readByte[kOneDArraySize];
            fileReader.read(reinterpret_cast<char *>(&readByte),
                            sizeof(uint8_t) * kOneDArraySize);
            auto img = std::vector<double>(readByte,
                   readByte + sizeof(readByte) / sizeof(readByte[0]));
            std::for_each(img.begin(), img.end(), [](double &d){ d /= 255.0; });
            imageBundle->push_back(img);
        }
        fileReader.close();
    }

    void getClasses(std::vector<uint8_t> *classBundle) {
        const int kOneDArraySize = unitCount;
        uint8_t readByte[kOneDArraySize];
        fileReader.read(reinterpret_cast<char *>(&readByte), sizeof(uint8_t) * kOneDArraySize);
        classBundle->assign(readByte, readByte + sizeof(readByte) + sizeof(readByte[0]));

        fileReader.close();
    }

    void getClasses(std::vector<std::vector<double>> *classBundle) {
        const int kOneDArraySize = unitCount;
        uint8_t readByte[kOneDArraySize];
        fileReader.read(reinterpret_cast<char *>(&readByte), sizeof(uint8_t) * kOneDArraySize);
        std::vector<uint8_t> readClasses(readByte, readByte + sizeof(readByte) + sizeof(readByte[0]));

        for (auto it = readClasses.begin(); it < readClasses.end(); it++) {
            std::vector<double> cls(10.0, 0);
            cls[*it] = 1.0;
            classBundle->push_back(cls);
        }
        fileReader.close();
    }
};

#endif  // LLAMA_CPP_EXAMPLE_MNIST_NN_MNISTREADER_H_
