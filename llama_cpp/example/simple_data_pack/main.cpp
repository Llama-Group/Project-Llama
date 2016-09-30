//
//  main.cpp
//  SimpleDataPack
//
//  Created by BlueCocoa on 2016/9/30.
//  Copyright © 2016 BlueCocoa. All rights reserved.
//

#include <iostream>
#include <string>
#include "SimpleDataPack.h"

class SimpleObject {
 public:
    int data;
};

int main(int argc, const char * argv[]) {
    SimpleDataPack pack;
    
    for (int i = 0; i < 4; i++) {
        bool flags = i & 0x1;
        pack.push(SimpleDataPack::data_t::BIT_8, "bool", &flags);
    }
    
    for (int i = 0; i < 4; i++) {
        int16_t int16 = UINT16_MAX - i;
        pack.push(SimpleDataPack::data_t::BIT_16, "int16", &int16, false);
    }
    
    for (int i = 0; i < 4; i++) {
        pack.push(SimpleDataPack::data_t::BIT_32, "int", &i);
    }
    
    for (int i = 0; i < 4; i++) {
        int64_t int64 = INT64_MAX - i;
        pack.push(SimpleDataPack::data_t::BIT_64, "int64", &int64);
    }
    
    for (int i = 0; i < 4; i++) {
        long double p = i * 233333.33333;
        pack.push(SimpleDataPack::data_t::BIT_128, "long double", &p);
    }
    
    pack.push_pure_data("cstring", reinterpret_cast<void *>("Hello\0"), 6);
    
    for (int i = 0; i < 4; i++) {
        SimpleObject object;
        object.data = i * 233;
        pack.push(SimpleDataPack::data_t::SIMPLE_OBJECT, "object", &object);
    }
    
    pack.saveTo("/Users/BlueCocoa/Desktop/233.dat");
    
    SimpleDataPack::loadFrom("/Users/BlueCocoa/Desktop/233.dat", [](
        uint16_t data_type, std::string id, void * data, size_t length, bool _signed) -> bool {
        switch (data_type) {
            case SimpleDataPack::data_t::BIT_8:
                std::cout << "BIT_8:\n";
                std::cout << "  id: " << id << '\n';
                std::cout << "  data: " << static_cast<int>(*(reinterpret_cast<char *>(data))) << '\n';
                std::cout << "  length: " << length << '\n';
                std::cout << "  _signed: " << (_signed ? "YES" : "NO") << '\n';
                break;
            case SimpleDataPack::data_t::BIT_16:
                std::cout << "BIT_16:\n";
                std::cout << "  id: " << id << '\n';
                std::cout << "  data: " << static_cast<uint16_t>(*(reinterpret_cast<uint16_t *>(data))) << '\n';
                std::cout << "  length: " << length << '\n';
                std::cout << "  _signed: " << (_signed ? "YES" : "NO") << '\n';
                break;
            case SimpleDataPack::data_t::BIT_32:
                std::cout << "BIT_32:\n";
                std::cout << "  id: " << id << '\n';
                std::cout << "  data: " << static_cast<int>(*(reinterpret_cast<int *>(data))) << '\n';
                std::cout << "  length: " << length << '\n';
                std::cout << "  _signed: " << (_signed ? "YES" : "NO") << '\n';
                break;
            case SimpleDataPack::data_t::BIT_64:
                std::cout << "BIT_64:\n";
                std::cout << "  id: " << id << '\n';
                std::cout << "  data: " << static_cast<int64_t>(*(reinterpret_cast<int64_t *>(data))) << '\n';
                std::cout << "  length: " << length << '\n';
                std::cout << "  _signed: " << (_signed ? "YES" : "NO") << '\n';
                break;
            case SimpleDataPack::data_t::BIT_128:
                std::cout << "BIT_128:\n";
                std::cout << "  id: " << id << '\n';
                std::cout << "  data: " << static_cast<long double>(*(reinterpret_cast<long double *>(data))) << '\n';
                std::cout << "  length: " << length << '\n';
                std::cout << "  _signed: " << (_signed ? "YES" : "NO") << '\n';
                break;
            case SimpleDataPack::data_t::SIMPLE_OBJECT:
                std::cout << "SIMPLE_OBJECT:\n";
                std::cout << "  id: " << id << '\n';
                std::cout << "  data: " << reinterpret_cast<SimpleObject *>(data)->data << '\n';
                std::cout << "  length: " << length << '\n';
                std::cout << "  _signed: " << (_signed ? "YES" : "NO") << '\n';
                break;
            case SimpleDataPack::data_t::PURE_DATA:
                std::cout << "PURE_DATA:\n";
                std::cout << "  id: " << id << '\n';
                std::cout << "  data: " << reinterpret_cast<char *>(data) << '\n';
                std::cout << "  length: " << length << '\n';
                std::cout << "  _signed: " << (_signed ? "YES" : "NO") << '\n';
                break;
            default:
                break;
        }
        return true;
    });
    return 0;
}