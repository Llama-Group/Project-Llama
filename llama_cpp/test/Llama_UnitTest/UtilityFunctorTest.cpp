
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

#include <gtest/gtest.h>
#include <string.h>
#include <Utility/Functor.h>

#include <string>

using std::string;

struct FunctorTest : public ::testing::Test {
    Functor functor_int  = Functor([]() -> int { return 1; });
    Functor functor_obj  = Functor([]() -> string { return "ok"; });

    int ref = 0;
    Functor functor_void = Functor([this]() -> void { this->ref = 1; });
};

// Return Value
TEST_F(FunctorTest, ReturnValue) {
    int result = functor_int.as<int>()();
    EXPECT_EQ(result, 1);
}

TEST_F(FunctorTest, ReturnObject) {
    const char * return_value_ptr = functor_obj.as<string>()().c_str();
    int result = strcmp(return_value_ptr, "ok");
    EXPECT_EQ(result, 0);
}

TEST_F(FunctorTest, NoReturn) {
    functor_void();
    EXPECT_EQ(ref, 1);
}
