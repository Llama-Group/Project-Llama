
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

#include <Utility/Functor.h>

#include <iostream>

using std::cout;

int main(int argc, const char * argv[]) {
    Functor test = []() -> void {
        std::cout << "ax^2 + bx + c:\n";

        Functor formular = [](int a) -> Functor {
            cout << "a inited to " << a << '\n';
            return [a](int b) -> Functor {
                cout << "with a = " << a << ", b inited to " << b << '\n';
                return [a, b](int c) -> Functor {
                    cout << "with a = " << a << ", b = " << b << ", c inited to " << c << '\n';
                    return [a, b, c](int x) -> int {
                        return a*x*x + b*x + c;
                    };
                };
            };
        };


        int a = 1, b = 2, c = 3, x = 4;
        cout << a << '*' << x << '*' << x << '+' << b << '*' << x << '+' << c << '\n';

        Functor formular_with_a   = formular.as<Functor>()(a);
        Functor formular_with_ab  = formular_with_a.as<Functor>()(b);
        Functor formular_with_abc = formular_with_ab.as<Functor>()(c);
        cout << formular_with_abc.as<int>()(x) << '\n';

        cout << formular.as<Functor>()(a)
        .as<Functor>()(b)
        .as<Functor>()(c)
        .as<int>()(x) << '\n';
    };
    test.as<void>()();
    return 0;
}
