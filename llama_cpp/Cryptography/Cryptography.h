//
//  Cryptography.h
//
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

#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <string>

namespace alpaca::cryptography {
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
};

#endif /* CRYPTOGRAPHY_H */
