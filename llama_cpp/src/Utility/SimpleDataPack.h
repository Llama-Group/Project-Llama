//
//  SimpleDataPack.h
//  SimpleDataPack
//
//  Created by BlueCocoa on 2016/9/30.
//  Copyright © 2016 BlueCocoa. All rights reserved.
//

#ifndef LLAMA_CPP_SRC_UTILITY_SIMPLEDATAPACK_H_
#define LLAMA_CPP_SRC_UTILITY_SIMPLEDATAPACK_H_

#include <stdlib.h>
#include <functional>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>

class SimpleDataPack {
public:
    typedef enum data_t : unsigned short {
        BIT_8           = 0b00000001,
        BIT_16          = 0b00000010,
        BIT_32          = 0b00000100,
        BIT_64          = 0b00001000,
        BIT_128         = 0b00010000,
        
        // Object with basic data type
        SIMPLE_OBJECT   = 0b00100000,
        
        // like void *
        PURE_DATA       = 0b01000000,
        
        // rest values are reserved
    } data_t;
    
    SimpleDataPack() {
        header = (struct savable_list_t *)malloc(sizeof(struct savable_list_t));
        header->next = nullptr;
        last = header;
    }
    
    ~SimpleDataPack() {
        struct savable_list_t * iterator = header;
        if (iterator->next) {
            do {
                struct savable_list_t * tmp = iterator;
                iterator = iterator->next;
                free(iterator->copied);
                free((void *)tmp);
            } while (iterator->next);
        }
        free(header);
    }
    
    template <typename T>
    void push(unsigned short data_type, std::string id, const T* data, bool _signed = true) {
        struct savable_list_t * item = (struct savable_list_t *)malloc(sizeof(struct savable_list_t));
        if (item) {
            memset(item, 0, sizeof(struct savable_list_t));
            item->data_type = (data_t)(_signed << 15);
            item->data_type |= data_type;
            item->id = std::make_shared<std::string>(id);
            
            item->copied = (void *)malloc(sizeof(T));
            if (item->copied) {
                memset(item->copied, 0, sizeof(T));
                memcpy(item->copied, data, sizeof(T));
                item->size = sizeof(T);
                item->next = nullptr;
                last->next = item;
                last = last->next;
                count++;
            } else {
                throw std::runtime_error("No enough memory");
            }
        } else {
            throw std::runtime_error("No enough memory");
        }
    }
    
    void push_pure_data(std::string id, void * data, int32_t length) {
        struct savable_list_t * item = (struct savable_list_t *)malloc(sizeof(struct savable_list_t));
        if (item) {
            memset(item, 0, sizeof(struct savable_list_t));
            item->data_type = (data_t)(true << 15);
            item->data_type |= data_t::PURE_DATA;
            item->id = std::make_shared<std::string>(id);
            
            item->copied = (void *)malloc(length);
            if (item->copied) {
                memset(item->copied, 0, length);
                memcpy(item->copied, data, length);
                item->size = length;
                item->next = nullptr;
                last->next = item;
                last = last->next;
                count++;
            } else {
                throw std::runtime_error("No enough memory");
            }
        } else {
            throw std::runtime_error("No enough memory");
        }
    }
    
    void loadFrom(std::string file, const std::function<bool(unsigned short data_type, std::string id, void * data, size_t length, bool _signed)>& callback) {
        static char head[4];
        
        std::ifstream loaded(file);
        if (loaded.is_open()) {
            loaded.read(head, 4);
            if (strcmp("SDP!", head) == 0) {
                int32_t _count = 0;
                loaded.read(reinterpret_cast<char *>(&_count), sizeof(int32_t));
                
                if (_count >= 0) {
                    unsigned short data_type;
                    bool _signed;
                    int32_t length;
                    for (int i = 0; i < _count; i++) {
                        loaded.read(reinterpret_cast<char *>(&data_type), sizeof(unsigned short));
                        _signed = (data_type >> 15);
                        data_type <<= 1;
                        data_type >>= 1;
                        
                        loaded.read(reinterpret_cast<char *>(&length), sizeof(int32_t));
                        char * buffer = (char *)malloc(length + 1);
                        memset(buffer, 0, length + 1);
                        loaded.read(buffer, length);
                        std::string id = std::string(buffer);
                        free((void *)buffer);
                        
                        void * data = malloc(length);
                        
                        loaded.read(reinterpret_cast<char *>(&length), sizeof(int32_t));
                        loaded.read(reinterpret_cast<char *>(data), length);
                        
                        if (!callback(data_type, id, data, length, _signed)) {
                            free(data);
                            break;
                        } else {
                            free(data);
                        }
                    }
                } else {
                    throw std::runtime_error("File format error");
                }
            } else {
                throw std::runtime_error("File format error");
            }
            loaded.close();
        } else {
            throw std::runtime_error("Cannot open file");
        }
    }
    
    void saveTo(std::string file) {
        std::ofstream saved(file);
        if (saved.is_open()) {
            saved.write("SDP!", 4);
            saved.write(reinterpret_cast<char *>(&count), sizeof(int32_t));
            
            struct savable_list_t * iterator = header;
            while ((iterator = iterator->next)) {
                auto&& id = iterator->id.get();
                
                saved.write(reinterpret_cast<char *>(&iterator->data_type), sizeof(unsigned short));
                int32_t id_length = (int32_t)id->length();
                saved.write(reinterpret_cast<char *>(&id_length), sizeof(int32_t));
                saved.write(id->c_str(), id->length());
                saved.write(reinterpret_cast<char *>(&iterator->size), sizeof(int32_t));
                saved.write(reinterpret_cast<char *>(iterator->copied), iterator->size);
            }
            saved.close();
        } else {
            throw std::runtime_error("Cannot open file");
        }
    }
private:
    typedef struct savable_list_t {
        unsigned short data_type;
        std::shared_ptr<std::string> id;
        int32_t size = 0;
        void * copied = nullptr;
        savable_list_t * next;
    } savable_list_t;
    
    struct savable_list_t * header, * last;
    
    int32_t count = 0;
};

#endif  // LLAMA_CPP_SRC_UTILITY_SIMPLEDATAPACK_H_
