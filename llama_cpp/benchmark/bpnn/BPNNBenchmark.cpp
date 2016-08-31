
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

#include "benchmark/benchmark.h"

#include <ML/NeuralNetwork.h>

using llama::NeuralNetwork;

double calcLogicAvgTotalError(NeuralNetwork *nn, double a, double b, double c, double d) {
    return nn->getTotalError({0, 0}, {a}) * 0.25 +
           nn->getTotalError({0, 1}, {b}) * 0.25 +
           nn->getTotalError({1, 0}, {c}) * 0.25 +
           nn->getTotalError({1, 1}, {d});
}

static void NNOverheadNormal(benchmark::State& state) {
    while (state.KeepRunning()) {
        NeuralNetwork nn({2, 5, 1});
    }
}

static void NNOverheadStress(benchmark::State& state) {
    while (state.KeepRunning()) {
        NeuralNetwork nn({2, 50, 50, 1});
    }
}

static void NNFeedNormal(benchmark::State& state) {
    NeuralNetwork nn({2, 5, 1});
    while (state.KeepRunning()) {
        nn.feed({1, 1});
    }
}

static void NNTrainAndNormal(benchmark::State& state) {
    NeuralNetwork nn({2, 5, 1});
    while (state.KeepRunning()) {
        while (calcLogicAvgTotalError(&nn, 0, 0, 0, 1) > 0.01) {
            nn.train({0, 0}, {0});
            nn.train({0, 1}, {0});
            nn.train({1, 0}, {0});
            nn.train({1, 1}, {1});
            trainCount++;
        }
    }
}

static void NNTrainXorNormal(benchmark::State& state) {
    NeuralNetwork nn({2, 5, 1});
    while (state.KeepRunning()) {
        while (calcLogicAvgTotalError(&nn, 0, 1, 1, 0) > 0.01) {
            nn.train({0, 0}, {0});
            nn.train({0, 1}, {1});
            nn.train({1, 0}, {1});
            nn.train({1, 1}, {0});
        }
    }
}

static void NNTrainAndStress(benchmark::State& state) {
    NeuralNetwork nn({2, 10, 10, 1});
    while (state.KeepRunning()) {
        while (calcLogicAvgTotalError(&nn, 0, 0, 0, 1) > 0.01) {
            nn.train({0, 0}, {0});
            nn.train({0, 1}, {0});
            nn.train({1, 0}, {0});
            nn.train({1, 1}, {1});
        }
    }
}

static void NNTrainAndComplete(benchmark::State& state) {
    while (state.KeepRunning()) {
        NeuralNetwork nn({2, 5, 1});
        nn.train(200, [&](){
            nn.train({0, 0}, {0});
            nn.train({0, 1}, {0});
            nn.train({1, 0}, {0});
            nn.train({1, 1}, {1});
        });
        if (calcLogicAvgTotalError(&nn, 0, 0, 0, 1) > 0.01) {
            while (calcLogicAvgTotalError(&nn, 0, 0, 0, 1) > 0.01) {
                nn.train({0, 0}, {0});
                nn.train({0, 1}, {0});
                nn.train({1, 0}, {0});
                nn.train({1, 1}, {1});
            }
        };
    }
}

BENCHMARK(NNOverheadNormal);
BENCHMARK(NNOverheadStress);
BENCHMARK(NNFeedNormal);
BENCHMARK(NNTrainAndNormal);
BENCHMARK(NNTrainXorNormal);
BENCHMARK(NNTrainAndStress);
BENCHMARK(NNTrainAndComplete);

BENCHMARK_MAIN();
