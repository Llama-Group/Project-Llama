
//
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#ifndef LLAMA_CPP_SRC_CRYPTOGRAPHY_CRYPTOGRAPHY_H_
#define LLAMA_CPP_SRC_CRYPTOGRAPHY_CRYPTOGRAPHY_H_

#include <string>

namespace alpaca {
namespace cryptography {
/**
 *  @brief Encode the plain text with public key
 *
 *  @param plaintext Plain text
 *  @param publickey The path of the public key
 *
 *  @return Cipher text or "" if failed
 */
std::string encode(const std::string& plaintext, const std::string& publickey);

/**
 *  @brief Decode the cipher text with private key
 *
 *  @param ciphertext Cipher text
 *  @param privatekey The path of the private key
 *
 *  @return Plain text or "" if failed
 */
std::string decode(const std::string& ciphertext, const std::string& privatekey);

};  // namespace cryptography
};  // namespace alpaca

#endif  // LLAMA_CPP_SRC_CRYPTOGRAPHY_CRYPTOGRAPHY_H_
