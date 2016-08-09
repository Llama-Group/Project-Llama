
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

#ifndef LLAMA_CPP_SRC_RNG_MERSENNETWISTER_H_
#define LLAMA_CPP_SRC_RNG_MERSENNETWISTER_H_

#include <stdint.h>
#include <sys/types.h>

namespace alpaca {
namespace RNG {

class MersenneTwister {
 public:
    explicit MersenneTwister(uint32_t seed);
    uint32_t rand();
 private:
    uint32_t state[624];
    size_t index;
    void reseed();
};

}  // namespace RNG
}  // namespace alpaca

#endif  // LLAMA_CPP_SRC_RNG_MERSENNETWISTER_H_
