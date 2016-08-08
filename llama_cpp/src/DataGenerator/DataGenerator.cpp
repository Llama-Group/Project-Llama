#include "DataGenerator.hpp"

template<typename T>
void llama::RandomData::generateRandomData(std::vector<T> *targetVector, int count) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(5.0, 2.0);
    
    for(int i = 0; i < count; i++) {
        targetVector->push_back(distribution(generator));
    }
}

template<>
void llama::RandomData::generateRandomData<int>(std::vector<int> *targetVector, int count) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(10.0, 4.0);
    
    for(int i = 0; i < count; i++) {
        targetVector->push_back(distribution(generator));
    }
}

template<>
void llama::RandomData::generateRandomData<bool>(std::vector<bool> *targetVector, int count) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(5.0, 2.0);
    
    for(int i = 0; i < count; i++) {
        targetVector->push_back(distribution(generator)>5.0 ? true:false);
    }
    
}

template<>
void llama::RandomData::generateRandomData<double>(std::vector<double> *targetVector, int count) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(5.0, 2.0);
    
    for(int i = 0; i < count; i++) {
        targetVector->push_back(distribution(generator));
    }
}