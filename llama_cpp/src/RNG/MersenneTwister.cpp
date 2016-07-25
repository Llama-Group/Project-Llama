//
//  MersenneTwister.h
//  Project Llama
//
//  Created by BlueCocoa on 2016/7/25.
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

#include "MersenneTwister.h"

using namespace llama::RNG;

MersenneTwister::MersenneTwister(uint32_t seed) {
    this->index = 0;
    this->state[0] = seed;
    for (size_t i = 1; i < 624; i++)
        this->state[i] = (i + 0x6C078965 * (this->state[i - 1] ^ (this->state[i - 1] >> 30))) & 0xFFFFFFFF;
}

uint32_t MersenneTwister::rand() {
    if (this->index == 0)
        this->reseed();
    
    uint32_t y = this->state[this->index];
    y ^= (y >> 11);
    y ^= (y <<  7) & 0x9D2C5680;
    y ^= (y << 15) & 0xEFC60000;
    y ^= (y >> 18);
    
    this->index = (this->index + 1) % 624;
    
    return y;
}

void MersenneTwister::reseed() {
    for (size_t i = 0; i < 624; i++) {
        uint32_t y = (this->state[i] & 0x80000000) + (this->state[(i + 1) % 624] & 0x7FFFFFFF);
        this->state[i] = this->state[(i + 397) % 624] ^ (y >> 1);
        if (y % 2 != 0)
            this->state[i] ^= 0x9908B0DF;
    }
}
