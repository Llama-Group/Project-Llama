
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

#include <Sort/hpSort.h>

#include <iostream>
#include <iterator>
#include <algorithm>

using std::cout;
using std::copy;
using std::ostream_iterator;

int main(int argc, const char * argv[]) {
    int array[11];
    auto restore = [&](int * x){
        x[0] = 12; x[1] = 2;  x[2] = 16;
        x[3] = 30; x[4] = 8;  x[5] = 28;
        x[6] = 4;  x[7] = 10; x[8] = 20;
        x[9] = 6;  x[10] = 18;
    };

    restore(array);
    alpaca::sort<int>(alpaca::BUBBLE_SORT, array, 11);

    copy(array, array + 11, ostream_iterator<int>(cout, " "));
    cout << '\n';

    restore(array);
    alpaca::sort<int>(alpaca::COCKTAIL_SORT, array, 11);
    copy(array, array + 11, ostream_iterator<int>(cout, " "));
    cout << '\n';

    restore(array);
    alpaca::sort<int>(alpaca::INSERTION_SORT, array, 11);
    copy(array, array + 11, ostream_iterator<int>(cout, " "));
    cout << '\n';

    restore(array);
    alpaca::sort<int>(alpaca::SELECTION_SORT, array, 11);
    copy(array, array + 11, ostream_iterator<int>(cout, " "));
    cout << '\n';

    restore(array);
    alpaca::sort<int>(alpaca::SHELL_SORT, array, 11);
    copy(array, array + 11, ostream_iterator<int>(cout, " "));
    cout << '\n';

    restore(array);
    alpaca::sort<int>(alpaca::QUICK_SORT, array, 11);
    copy(array, array + 11, ostream_iterator<int>(cout, " "));
    cout << '\n';

    return 0;
}
