//
//  Cryptography.cpp
//
//  Created by BlueCocoa on 2016/7/22.
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#include "Cryptography.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

using namespace std;

string alpaca::cryptography::encode(const string& plaintext, const string& publickey) {
    string result = "";
    if (plaintext.empty() || publickey.empty()) return result;
    
    FILE * key = fopen(publickey.c_str(), "rb");
    if (key == nullptr) return result;
    
    RSA * RSAPublicKey = RSA_new();
    if (PEM_read_RSA_PUBKEY(key, &RSAPublicKey, 0, 0) == nullptr) return result;
    
    ssize_t len = RSA_size(RSAPublicKey);
    char * encode = new char[len + 1];
    int ret = RSA_public_encrypt((int)plaintext.length(), (const unsigned char *)plaintext.c_str(), (unsigned char *)encode, RSAPublicKey, RSA_PKCS1_PADDING);
    if (ret > 0) result = string(encode, ret);
    
    delete[] encode;
    RSA_free(RSAPublicKey);
    fclose(key);
    CRYPTO_cleanup_all_ex_data();
    return result;
}

string alpaca::cryptography::decode(const string &ciphertext, const string& privatekey) {
    string result = "";
    if (ciphertext.empty() || privatekey.empty()) return result;
    
    FILE * key = fopen(privatekey.c_str(), "rb");
    if (key == nullptr) return result;
    
    RSA * RSAPrivateKey = RSA_new();
    if (PEM_read_RSAPrivateKey(key, &RSAPrivateKey, 0, 0) == nullptr) return result;
    
    ssize_t len = RSA_size(RSAPrivateKey);
    char * decode = new char[len + 1];
    
    int ret = RSA_private_decrypt((int)ciphertext.length(), (const unsigned char *)ciphertext.c_str(), (unsigned char*)decode, RSAPrivateKey, RSA_PKCS1_PADDING);
    if (ret > 0) result = std::string(decode, ret);
    
    delete[] decode;
    RSA_free(RSAPrivateKey);
    fclose(key);
    CRYPTO_cleanup_all_ex_data();
    return result;
}
