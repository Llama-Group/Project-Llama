
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License,Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at:
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing,software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include <Cryptography/Cryptography.h>

#include <unistd.h>

#include <iostream>
#include <string>


using std::cout;
using std::string;

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

int main(int argc, const char * argv[]) {
    char temp[PATH_MAX];
    getcwd(temp, PATH_MAX);
    string argv_str(argv[0]);
    string base = argv_str.substr(0, argv_str.find_last_of("/"));
    chdir(base.c_str());
    cout << alpaca::cryptography::decode(alpaca::cryptography::encode("Hello, World!\n", "public.pem"), "private.pem");
    chdir(temp);
}
