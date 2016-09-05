
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

#include <ifstream>
#include <string>
#include <vector>

#define IDX3_MAGIX 0x00000803;
#define IDX1_MAGIC 0x00000801;

enum FileType = {IDX3, IDX1};

class MNISTReader {
 public:
    MNISTReader() {}

	MNISTReader(std::string trainImagesPath, std::string trainClassesPath,
				std::string testImagesPath, std::string testClassesPath) {
		mTrainImagesPath = trainImagesPath;
		mTrainClassesPath = trainClassesPath;
		mTestImagesPath = testImagesPath;
		mTestClassesPath = testClassesPath;
	}

	void getImages(std::vector<std::vector<std::vector<uint8_t>>> *imageBundle) {
		
	}

 private:
	ifstream fileReader;

	std::string mTrainImagesPath;
	std::string mTrainClassesPath;
	std::string mTestImagesPath;
	std::string mTestClassesPath;

	FileType currentType;
	int unitCount;
	int row;
	int column;

	void setup(std::string filePath) {
		fileReader = open(filePath, std::ios::binary);
		// TODO(anyone): add file successfully opened check here.
		
	}
};

