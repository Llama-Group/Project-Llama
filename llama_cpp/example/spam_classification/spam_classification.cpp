
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

#include <ML/NaiveBayesClassifier.h>

#include <vector>

//  Table 1 contains (pretend!) training data for a naive Bayes spam filter
//  where the goal is to predict spam based on whether the words “Viagra”
//  and/or “Funds” appear in an incoming email.
//
//  The data was produced from 50 emails.
//  To understand the format of Table 1 note that the first line of the table
//  states that 9 spam emails have been observed which contain
//  neither “Viagra” nor “Funds”.
//
//  The second line states that 4 spam emails have been observed
//  where “Funds” was in the email, but “Viagra” was not.
//
//  The other lines present data in the same way.
//
//  Spam    “Viagra”    “Funds” Frequency
//  y       n           n       9
//  y       n           y       4
//  y       y           n       5
//  y       y           y       1
//  n       n           n       28
//  n       n           y       2
//  n       y           n       1
//  n       y           y       0
//              Table 1.

using std::vector;
using std::cout;
using std::endl;

int main() {
    vector<int> y = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    vector<int> n = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0};

    vector<vector<int>> features;

    // Gather train data
    features.push_back(y);
    features.push_back(n);

    vector<bool> cls;

    // Gather class data
    for (int i = 0; i < 19; i++)
        cls.push_back(true);
    for (int i = 0; i < 31; i++)
        cls.push_back(false);

    // Create classifier
    llama::NaiveBayesClassifier BC = llama::NaiveBayesClassifier(features, cls);

    cout << "An email contains Viagra and Funds, ths probability for it to be a spam email is: "
      << BC.getProbability({1, 1}, true)*100 << "%" << endl;
    cout << "An email does not contain Viagra and Funds, ths probability for it to be a spam email is: "
      << BC.getProbability({0, 0}, true)*100 << "%" << endl;
}
