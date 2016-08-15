
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

#include <Utility/LLObject.h>
#include <iostream>
#include <string>

using llama::LLObject;

int main() {
    LLObject integer = LLObject(1);
    std::cout << integer.cast<int>() << '\n';
    std::cout << integer.is<int>() << '\n';
    std::cout << integer.is<double>() << '\n';

    integer = LLObject(2);
    std::cout << integer.cast<int>() << '\n';

    int implicit_cast = integer;
    std::cout << implicit_cast << '\n';

    const LLObject floating_const = LLObject(2.0f);
    std::cout << floating_const.cast<double>() << '\n';

    LLObject floating = LLObject(floating_const);
    std::cout << floating.cast<double>() << '\n';

    floating = LLObject(LLObject(2.33f));
    std::cout << floating.cast<double>() << '\n';

    LLObject copy_floating = LLObject(&floating);
    std::cout << copy_floating.cast<double>() << '\n';

    LLObject function = LLObject(Functor([]() -> int {
        return 1;
    }));
    std::cout << function.as<int>()() << '\n';

    function = Functor([&](const std::string& new_string) -> LLObject {
        return LLObject(new_string);
    });

    LLObject stl_string = LLObject(std::string("Hello"));
    std::cout << stl_string.cast<std::string>() << ' ';

    std::cout << function.as<LLObject>()(std::string("World!")).cast<std::string>() << '\n';
    return 0;
}
