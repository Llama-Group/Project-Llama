
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

#include <iostream>
#include <vector>

#include "NeuralNetwork.h"

using std::cout;
using std::vector;

using llama::NeuralNetwork;

int main(int argc, const char * argv[])
{
	vector<int> layers = {2,3,1};
	
	NeuralNetwork nn = NeuralNetwork(layers);
	
	cout << nn.calculateWithFeeding({1,1})[0] << '\n';
	
	return 0;
}
