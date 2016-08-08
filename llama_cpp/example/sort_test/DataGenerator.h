

#ifndef DataGenerator_hpp
#define DataGenerator_hpp

#include <iostream>
#include <vector>

namespace llama {
    class DataGenerator {
    public:
        DataGenerator() {}

        void generateSequenceVector(std::vector<int> *targetVector, int count=5, bool reverse=true);
    };
}

#endif /* DataGenerator_hpp */
