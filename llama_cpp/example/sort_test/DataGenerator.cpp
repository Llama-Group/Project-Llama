

#include "DataGenerator.h"

void llama::DataGenerator::generateSequenceVector(std::vector<int> *targetVector, int count, bool reverse) {
    for (int i = 0; i < count; i++) {
        targetVector->push_back(reverse ? count - i : i + 1);
    }
}
