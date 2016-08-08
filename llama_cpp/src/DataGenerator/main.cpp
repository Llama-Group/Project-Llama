#include <iostream>
#include "DataGenerator.hpp"

int main(int argc, const char * argv[]) {
    std::vector<int> a;
    std::vector<bool> b;
    std::vector<double> c;
    llama::RandomData mRandomData = llama::RandomData();
    int ct = 20;
    
    mRandomData.generateRandomData(&a, ct);
    
    for(const auto &n : a) {
        std::cout << n << std::endl;
    }
    
    std::cout << "==========" << std::endl;
    
    mRandomData.generateRandomData(&b, ct);
    
    for(const auto &n : b) {
        std::cout << n << std::endl;
    }
    
    std::cout << "==========" << std::endl;
    
    mRandomData.generateRandomData(&c, ct);
    
    for(const auto &n : c) {
        std::cout << n << std::endl;
    }
    
}
