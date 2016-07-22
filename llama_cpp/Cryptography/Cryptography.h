//
//  Cryptography.h
//  Alpaca
//
//  Created by BlueCocoa on 2016/7/22.
//  Copyright © 2016 BlueCocoa. All rights reserved.
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
