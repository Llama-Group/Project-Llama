//
//  llama.h
//  Project-LLama
//
//  Created by BlueCocoa on 2016/8/23.
//  Copyright © 2016 BlueCocoa. All rights reserved.
//

#ifndef LLAMA_CPP_SRC_LLAMA_H_
#define LLAMA_CPP_SRC_LLAMA_H_

/**
 *  @brief Compiler extension
 *
 *  @link  http://clang.llvm.org/docs/LanguageExtensions.html
 */

#ifndef __has_feature                       // Optional of course.
    #define __has_feature(x) 0              // Compatibility with non-clang compilers.
#endif
#ifndef __has_extension
    #define __has_extension __has_feature   // Compatibility with pre-3.0 compilers.
#endif

/**
 *  @brief Deprecated attribute
 *
 *  @discussion Provide a transitional period for users if there is or going to be any API change
 */
#if __has_extension(attribute_deprecated_with_message)
    #ifndef LLAMA_DEPRECATED
        #define LLAMA_DEPRECATED(message) __attribute__((deprecated (message)))
    #endif
#else
    #ifndef LLAMA_DEPRECATED
        #define LLAMA_DEPRECATED(message) __attribute__((deprecated))
    #endif
#endif

#endif  // LLAMA_CPP_SRC_LLAMA_H_
