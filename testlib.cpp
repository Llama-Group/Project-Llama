

#include "benchmark/benchmark.h"
#include <vector>
#include <algorithm>

static void StdSortInt(benchmark::State& state) {
	std::vector<int> a = {5, 4, 3, 2, 1};
	while (state.KeepRunning()) {
		std::sort(a.begin(), a.end());
	}
}

BENCHMARK(StdSortInt);

BENCHMARK_MAIN();
