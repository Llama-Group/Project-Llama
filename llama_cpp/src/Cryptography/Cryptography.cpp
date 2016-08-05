
//
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include <Cryptography/Cryptography.h>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#include <string>

using std::string;

string alpaca::cryptography::encode(const string& plaintext, const string& publickey) {
    string result = "";
    if (plaintext.empty() || publickey.empty()) return result;

    FILE * key = fopen(publickey.c_str(), "rb");
    if (key == nullptr) return result;

    RSA * RSAPublicKey = RSA_new();
    if (PEM_read_RSA_PUBKEY(key, &RSAPublicKey, 0, 0) == nullptr) return result;

    ssize_t len = RSA_size(RSAPublicKey);
    char * encode = new char[len + 1];
    int ret = RSA_public_encrypt(static_cast<int>(plaintext.length()),
                                 reinterpret_cast<const unsigned char *>(plaintext.c_str()),
                                 reinterpret_cast<unsigned char*>(encode), RSAPublicKey, RSA_PKCS1_PADDING);
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

    int ret = RSA_private_decrypt(static_cast<int>(ciphertext.length()),
                                  reinterpret_cast<const unsigned char *>(ciphertext.c_str()),
                                  reinterpret_cast<unsigned char*>(decode), RSAPrivateKey, RSA_PKCS1_PADDING);
    if (ret > 0) result = std::string(decode, ret);

    delete[] decode;
    RSA_free(RSAPrivateKey);
    fclose(key);
    CRYPTO_cleanup_all_ex_data();
    return result;
}
