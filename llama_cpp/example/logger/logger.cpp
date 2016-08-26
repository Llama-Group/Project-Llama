
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

#include <Utility/Logger.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

using llama::Logger;
using llama::LoggerWrapper;

class MyStream {
 public:
    template <typename T>
    MyStream& operator<<(const T& _) {
        std::cout << _;
        std::cout.flush();
        return *this;
    }

    MyStream& flush() {
        return *this;
    }
};

int main(int argc, const char * argv[]) {
    Logger clogLogger(std::clog);
    std::ofstream logfile("log");
    Logger fileLogger(logfile);

    MyStream stream;
    LoggerWrapper<MyStream> myLogger(stream);

    LLAMA_LOG_DEBUG(clogLogger, "This is a debug message\n");
    LLAMA_LOG_DEBUG(myLogger, "This is a debug message, and this line goes through MyStream\n");
    LLAMA_LOG_DEBUG(fileLogger, "This is a debug message, and this line goes into a file\n");
    LLAMA_LOG_DEBUG_TAG(clogLogger, "tag", "This is a tagged debug message\n");
    LLAMA_LOG_DEBUG_TAG(myLogger, "tag", "This is a tagged debug message, and this line goes through MyStream\n");
    LLAMA_LOG_DEBUG_TAG(fileLogger, "tag", "This is a tagged debug message, and this line goes into a file\n");

    LLAMA_LOG_INFO(clogLogger, "This is an info message\n");
    LLAMA_LOG_INFO(myLogger, "This is an info message, and this line goes through MyStream\n");
    LLAMA_LOG_INFO(fileLogger, "This is an info message, and this line goes into a file\n");
    LLAMA_LOG_INFO_TAG(clogLogger, "tag", "This is a tagged info message\n");
    LLAMA_LOG_INFO_TAG(myLogger, "tag", "This is a tagged info message, and this line goes through MyStream\n");
    LLAMA_LOG_INFO_TAG(fileLogger, "tag", "This is a tagged info message, and this line goes into a file\n");

    LLAMA_LOG_WARNING(clogLogger, "This is a warning message\n");
    LLAMA_LOG_WARNING(myLogger, "This is a warning message, and this line goes through MyStream\n");
    LLAMA_LOG_WARNING(fileLogger, "This is a warning message, and this line goes into a file\n");
    LLAMA_LOG_WARNING_TAG(clogLogger, "tag", "This is a tagged warning message\n");
    LLAMA_LOG_WARNING_TAG(myLogger, "tag", "This is a tagged warning message, and this line goes through MyStream\n");
    LLAMA_LOG_WARNING_TAG(fileLogger, "tag", "This is a tagged warning message, and this line goes into a file\n");

    LLAMA_LOG_ERROR(clogLogger, "This is an error message\n");
    LLAMA_LOG_ERROR(myLogger, "This is an error message, and this line goes through MyStream\n");
    LLAMA_LOG_ERROR(fileLogger, "This is an error message, and this line goes into a file\n");
    LLAMA_LOG_ERROR_TAG(clogLogger, "tag", "This is a tagged error message\n");
    LLAMA_LOG_ERROR_TAG(myLogger, "tag", "This is a tagged error message, and this line goes through MyStream\n");
    LLAMA_LOG_ERROR_TAG(fileLogger, "tag", "This is a tagged error message, and this line goes into a file\n");

    std::vector<std::thread> thread_safe;
    for (int i = 0; i < 10; i++) {
        thread_safe.emplace_back(std::thread([&]() {
            LLAMA_LOG_DEBUG(clogLogger, "This", " is", " also", " a", " thread", " safe", " logger\n");
            LLAMA_LOG_DEBUG(fileLogger, "And", " this", " is", " also", " a", " thread", " safe", " logger\n");
            LLAMA_LOG_DEBUG_TAG(clogLogger,
                "tag", "This", " is", " also", " a", " tagged", " thread", " safe", " logger\n");
            LLAMA_LOG_DEBUG_TAG(fileLogger,
                "tag", "And", " this", " is", " also", " a", " tagged", " thread", " safe", " logger\n");
        }));
    }
    std::for_each(thread_safe.begin(), thread_safe.end(), [](std::thread& t){
        t.join();
    });

    LLAMA_LOG_ERROR_X(clogLogger, "This is an error message, and this program should be terminated\n");
    LLAMA_LOG_ERROR_X(fileLogger, "This is an error message, and this line shall never be executed\n");
    LLAMA_LOG_ERROR_X_TAG(clogLogger, "tag", "This is a tagged error message, and this line shall never be executed\n");
    LLAMA_LOG_ERROR_X_TAG(fileLogger, "tag", "This is a tagged error message, and this line shall never be executed\n");
    return 0;
}
