
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

#include <gtest/gtest.h>
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

struct FunctorTest : public ::testing::Test {
};

// Debug message - Standard ostream (e.g std::clog, std::cout, std::cerr)
TEST_F(FunctorTest, StandardOstreamDebug) {
    Logger clogLogger(std::clog);
    LLAMA_LOG_DEBUG(clogLogger, "This is a debug message\n");
}

// Debug message - File ostream
TEST_F(FunctorTest, FileOstreamDebug) {
    std::ofstream logfile("log");
    Logger fileLogger(logfile);
    LLAMA_LOG_DEBUG(fileLogger, "This is a debug message, and this line goes into a file\n");
}

// Debug message - Custom ostream
TEST_F(FunctorTest, CustomOstreamDebug) {
    MyStream stream;
    LoggerWrapper<MyStream> myLogger(stream);
    LLAMA_LOG_DEBUG(myLogger, "This is a debug message, and this line goes through MyStream\n");
}

// Info message - Standard ostream (e.g std::clog, std::cout, std::cerr)
TEST_F(FunctorTest, StandardOstreamInfo) {
    Logger clogLogger(std::clog);
    LLAMA_LOG_INFO(clogLogger, "This is an info message\n");
}

// Info message - File ostream
TEST_F(FunctorTest, FileOstreamInfo) {
    std::ofstream logfile("log");
    Logger fileLogger(logfile);
    LLAMA_LOG_INFO(fileLogger, "This is an info message, and this line goes into a file\n");
}

// Info message - Custom ostream
TEST_F(FunctorTest, CustomOstreamInfo) {
    MyStream stream;
    LoggerWrapper<MyStream> myLogger(stream);
    LLAMA_LOG_INFO(myLogger, "This is an info message, and this line goes through MyStream\n");
}

// Warning message - Standard ostream (e.g std::clog, std::cout, std::cerr)
TEST_F(FunctorTest, StandardOstreamWarning) {
    Logger clogLogger(std::clog);
    LLAMA_LOG_WARNING(clogLogger, "This is a warning message\n");
}

// Warning message - File ostream
TEST_F(FunctorTest, FileOstreamWarning) {
    std::ofstream logfile("log");
    Logger fileLogger(logfile);
    LLAMA_LOG_WARNING(fileLogger, "This is a warning message, and this line goes into a file\n");
}

// Warning message - Custom ostream
TEST_F(FunctorTest, CustomOstreamWarning) {
    MyStream stream;
    LoggerWrapper<MyStream> myLogger(stream);
    LLAMA_LOG_WARNING(myLogger, "This is a warning message, and this line goes through MyStream\n");
}

// Error message - Standard ostream (e.g std::clog, std::cout, std::cerr)
TEST_F(FunctorTest, StandardOstreamError) {
    Logger clogLogger(std::clog);
    LLAMA_LOG_ERROR(clogLogger, "This is an error message\n");
}

// Error message - File ostream
TEST_F(FunctorTest, FileOstreamError) {
    std::ofstream logfile("log");
    Logger fileLogger(logfile);
    LLAMA_LOG_ERROR(fileLogger, "This is an error message, and this line goes into a file\n");
}

// Error message - Custom ostream
TEST_F(FunctorTest, CustomOstreamError) {
    MyStream stream;
    LoggerWrapper<MyStream> myLogger(stream);
    LLAMA_LOG_ERROR(myLogger, "This is an error message, and this line goes through MyStream\n");
}

// Error message and exit  - Standard ostream (e.g std::clog, std::cout, std::cerr)
TEST_F(FunctorTest, StandardOstreamErrorX) {
    Logger clogLogger(std::clog);
    ASSERT_DEATH({
        LLAMA_LOG_ERROR_X(clogLogger, "This is an error message\n");},
        "Error and exit\n");
}

// Error message and exit - File ostream
TEST_F(FunctorTest, FileOstreamErrorX) {
    std::ofstream logfile("log");
    Logger fileLogger(logfile);
    ASSERT_DEATH({
        LLAMA_LOG_ERROR_X(fileLogger, "This is an error message, and this line goes into a file\n");},
        "Error and exit\n");
}

// Error message and exit - Custom ostream
TEST_F(FunctorTest, CustomOstreamErrorX) {
    MyStream stream;
    LoggerWrapper<MyStream> myLogger(stream);
    ASSERT_DEATH({
        LLAMA_LOG_ERROR_X(myLogger, "This is an error message, and this line goes through MyStream\n");},
        "Error and exit\n");
}
