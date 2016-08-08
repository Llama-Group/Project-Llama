#include "DataGenerator.hpp"

template<typename T>
void llama::RandomData::generateRandomData(std::vector<T> *targetVector, int count) {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(10.0, 4.0);
    
    for(int i = 0; i < count; i++) {
        targetVector->push_back(distribution(generator));
    }
}

template<>
void llama::RandomData::generateRandomData<int>(std::vector<int> *targetVector, int count) {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(10.0, 4.0);
    
    for(int i = 0; i < count; i++) {
        targetVector->push_back(distribution(generator));
    }
}

template<>
void llama::RandomData::generateRandomData<bool>(std::vector<bool> *targetVector, int count) {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(10.0, 9.0);
    
    for(int i = 0; i < count; i++) {
        targetVector->push_back(distribution(generator)>10.0 ? true:false);
    }
    
}

template<>
void llama::RandomData::generateRandomData<double>(std::vector<double> *targetVector, int count) {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(10.0, 4.0);
    
    for(int i = 0; i < count; i++) {
        targetVector->push_back(distribution(generator));
    }
}