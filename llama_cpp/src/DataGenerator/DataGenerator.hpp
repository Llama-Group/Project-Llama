

#ifndef DataGenerator_hpp
#define DataGenerator_hpp

#include <stdio.h>
#include <vector>
#include <random>

namespace llama {
    class RandomData {
    public:
        RandomData() {}
        
        
        template<typename T>
        void generateRandomData(std::vector<T> *targetVector, int count);
    };
    
    template<>
    void RandomData::generateRandomData<int>(std::vector<int> *targetVector, int count);
    
    template<>
    void RandomData::generateRandomData<bool>(std::vector<bool> *targetVector, int count);
    
    template<>
    void RandomData::generateRandomData<double>(std::vector<double> *targetVector, int count);
    
    
}

#endif /* DataGenerator_hpp */
