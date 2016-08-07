
#include "benchmark/benchmark.h"

#include "Sort/BruteForceSort.h"
#include "Sort/InsertionSort.h"
#include "Sort/SelectionSort.h"
#include "Sort/BubbleSort.h"

static void StdSortInt(benchmark::State& state) {
    std::vector<int> a = {5, 4, 3, 2, 1};
    while (state.KeepRunning()) {
        std::sort(a.begin(), a.end());
    }
}

static void StdSortString(benchmark::State& state) {
    std::vector<std::string> a = {"5", "4", "3", "2", "1"};
    while (state.KeepRunning()) {
        std::sort(a.begin(), a.end());
    }
}

// BFSort
static void BFSortInt(benchmark::State& state) {
    llama::BruteForceSort<int> bfSort = llama::BruteForceSort<int>();
    std::vector<int> a = {5, 4, 3, 2, 1};
    while (state.KeepRunning()) {
        bfSort.performSort(&a);
    }
}

static void BFSortString(benchmark::State& state) {
    llama::BruteForceSort<std::string> bfSort = llama::BruteForceSort<std::string>();
    std::vector<std::string> a = {"5", "4", "3", "2", "1"};
    while (state.KeepRunning()) {
        bfSort.performSort(&a);
    }
}

static void BFSortDouble(benchmark::State& state) {
    llama::BruteForceSort<double> bfSort = llama::BruteForceSort<double>();
    std::vector<double> a = {5.0, 4.0, 3.0, 2.0, 1.0};
    while (state.KeepRunning()) {
        bfSort.performSort(&a);
    }
}

// Insort
static void InsortInt(benchmark::State& state) {
    llama::InsertionSort<int> InSort = llama::InsertionSort<int>();
    std::vector<int> a = {5, 4, 3, 2, 1};
    while (state.KeepRunning()) {
        InSort.performSort(&a);
    }
}

static void InsortString(benchmark::State& state) {
    llama::InsertionSort<std::string> InSort = llama::InsertionSort<std::string>();
    std::vector<std::string> a = {"5", "4", "3", "2", "1"};
    while (state.KeepRunning()) {
        InSort.performSort(&a);
    }
}

static void InsortDouble(benchmark::State& state) {
    llama::InsertionSort<double> Insort = llama::InsertionSort<double>();
    std::vector<double> a = {5.0, 4.0, 3.0, 2.0, 1.0};
    while (state.KeepRunning()) {
        Insort.performSort(&a);
    }
}
// SelctionSort
static void SeSortInt(benchmark::State& state) {
    llama::SelectionSort<int> SeSort = llama::SelectionSort<int>();
    std::vector<int> a = {5, 4, 3, 2, 1};
    while (state.KeepRunning()) {
        SeSort.performSort(&a);
    }
}

static void SeSortString(benchmark::State& state) {
    llama::SelectionSort<std::string> SeSort = llama::SelectionSort<std::string>();
    std::vector<std::string> a = {"5", "4", "3", "2", "1"};
    while (state.KeepRunning()) {
        SeSort.performSort(&a);
    }
}

static void SeSortDouble(benchmark::State& state) {
    llama::SelectionSort<double> SeSort = llama::SelectionSort<double>();
    std::vector<double> a = {5.0, 4.0, 3.0, 2.0, 1.0};
    while (state.KeepRunning()) {
        SeSort.performSort(&a);
    }
}

// BubbleSort
static void BuSortInt(benchmark::State& state) {
    llama::BubbleSort<int> BuSort = llama::BubbleSort<int>();
    std::vector<int> a = {5, 4, 3, 2, 1};
    while (state.KeepRunning()) {
        BuSort.performSort(&a);
    }
}

static void BuSortString(benchmark::State& state) {
    llama::BubbleSort<std::string> BuSort = llama::BubbleSort<std::string>();
    std::vector<std::string> a = {"5", "4", "3", "2", "1"};
    while (state.KeepRunning()) {
        BuSort.performSort(&a);
    }
}

static void BuSortDouble(benchmark::State& state) {
    llama::BubbleSort<double> BuSort = llama::BubbleSort<double>();
    std::vector<double> a = {5.0, 4.0, 3.0, 2.0, 1.0};
    while (state.KeepRunning()) {
        BuSort.performSort(&a);
    }
}

class CustomisedClass {
public:
    CustomisedClass() {}
    CustomisedClass(int input) {
        this->input = input*10;
    }

    int getInput() const {
        return input;
    }

    operator std::string() const
    {
        return "CustomisedClass: "+std::to_string(getInput());
    }

private:
    int input;
};
namespace llama {
    template<>
    double SortObject<CustomisedClass>::getValue() const {
        return (double) (obj.getInput());
    }
}

static void BFSortClass(benchmark::State& state) {
    llama::BruteForceSort<CustomisedClass> bfSort = llama::BruteForceSort<CustomisedClass>();
    std::vector<CustomisedClass> a = {CustomisedClass(5), CustomisedClass(4),
                          CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};
    while (state.KeepRunning()) {
        bfSort.performSort(&a);
    }
}

static void InsortClass(benchmark::State& state) {
    llama::InsertionSort<CustomisedClass> Insort = llama::InsertionSort<CustomisedClass>();
    std::vector<CustomisedClass> a = {CustomisedClass(5), CustomisedClass(4),
                          CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};
    while (state.KeepRunning()) {
        Insort.performSort(&a);
    }
}
static void SeSortClass(benchmark::State& state) {
    llama::SelectionSort<CustomisedClass> SeSort = llama::SelectionSort<CustomisedClass>();
    std::vector<CustomisedClass> a = {CustomisedClass(5), CustomisedClass(4),
                          CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};
    while (state.KeepRunning()) {
        SeSort.performSort(&a);
    }
}

static void BuSortClass(benchmark::State& state) {
    llama::BubbleSort<CustomisedClass> BuSort = llama::BubbleSort<CustomisedClass>();
    std::vector<CustomisedClass> a = {CustomisedClass(5), CustomisedClass(4),
                          CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};
    while (state.KeepRunning()) {
        BuSort.performSort(&a);
    }
}

BENCHMARK(StdSortInt);
BENCHMARK(StdSortString);
BENCHMARK(BFSortInt);
BENCHMARK(BFSortString);
BENCHMARK(BFSortDouble);
BENCHMARK(BFSortClass);
BENCHMARK(InsortInt);
BENCHMARK(InsortString);
BENCHMARK(InsortDouble);
BENCHMARK(InsortClass);
BENCHMARK(SeSortInt);
BENCHMARK(SeSortString);
BENCHMARK(SeSortDouble);
BENCHMARK(SeSortClass);
BENCHMARK(BuSortInt);
BENCHMARK(BuSortString);
BENCHMARK(BuSortDouble);
BENCHMARK(BuSortClass);

BENCHMARK_MAIN();
