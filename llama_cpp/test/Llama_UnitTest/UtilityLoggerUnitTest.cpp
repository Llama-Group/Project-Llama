
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

struct LoggerTest : public ::testing::Test {
};

// Debug message - Standard ostream (e.g std::clog, std::cout, std::cerr)
TEST_F(LoggerTest, StandardOstreamDebug) {
    Logger clogLogger(std::clog);
    LLAMA_LOG_DEBUG(clogLogger, "This is a debug message\n");
}

// Debug message - File ostream
TEST_F(LoggerTest, FileOstreamDebug) {
    std::ofstream logfile("log", std::ofstream::out | std::ofstream::app);
    Logger fileLogger(logfile);
    LLAMA_LOG_DEBUG(fileLogger, "This is a debug message, and this line goes into a file\n");
    logfile.close();
}

// Debug message - Custom ostream
TEST_F(LoggerTest, CustomOstreamDebug) {
    MyStream stream;
    LoggerWrapper<MyStream> myLogger(stream);
    LLAMA_LOG_DEBUG(myLogger, "This is a debug message, and this line goes through MyStream\n");
}

// Info message - Standard ostream (e.g std::clog, std::cout, std::cerr)
TEST_F(LoggerTest, StandardOstreamInfo) {
    Logger clogLogger(std::clog);
    LLAMA_LOG_INFO(clogLogger, "This is an info message\n");
}

// Info message - File ostream
TEST_F(LoggerTest, FileOstreamInfo) {
    std::ofstream logfile("log", std::ofstream::out | std::ofstream::app);
    Logger fileLogger(logfile);
    LLAMA_LOG_INFO(fileLogger, "This is an info message, and this line goes into a file\n");
    logfile.close();
}

// Info message - Custom ostream
TEST_F(LoggerTest, CustomOstreamInfo) {
    MyStream stream;
    LoggerWrapper<MyStream> myLogger(stream);
    LLAMA_LOG_INFO(myLogger, "This is an info message, and this line goes through MyStream\n");
}

// Warning message - Standard ostream (e.g std::clog, std::cout, std::cerr)
TEST_F(LoggerTest, StandardOstreamWarning) {
    Logger clogLogger(std::clog);
    LLAMA_LOG_WARNING(clogLogger, "This is a warning message\n");
}

// Warning message - File ostream
TEST_F(LoggerTest, FileOstreamWarning) {
    std::ofstream logfile("log", std::ofstream::out | std::ofstream::app);
    Logger fileLogger(logfile);
    LLAMA_LOG_WARNING(fileLogger, "This is a warning message, and this line goes into a file\n");
    logfile.close();
}

// Warning message - Custom ostream
TEST_F(LoggerTest, CustomOstreamWarning) {
    MyStream stream;
    LoggerWrapper<MyStream> myLogger(stream);
    LLAMA_LOG_WARNING(myLogger, "This is a warning message, and this line goes through MyStream\n");
}

// Error message - Standard ostream (e.g std::clog, std::cout, std::cerr)
TEST_F(LoggerTest, StandardOstreamError) {
    Logger clogLogger(std::clog);
    LLAMA_LOG_ERROR(clogLogger, "This is an error message\n");
}

// Error message - File ostream
TEST_F(LoggerTest, FileOstreamError) {
    std::ofstream logfile("log", std::ofstream::out | std::ofstream::app);
    Logger fileLogger(logfile);
    LLAMA_LOG_ERROR(fileLogger, "This is an error message, and this line goes into a file\n");
    logfile.close();
}

// Error message - Custom ostream
TEST_F(LoggerTest, CustomOstreamError) {
    MyStream stream;
    LoggerWrapper<MyStream> myLogger(stream);
    LLAMA_LOG_ERROR(myLogger, "This is an error message, and this line goes through MyStream\n");
}

// Error message and exit  - Standard ostream (e.g std::clog, std::cout, std::cerr)
TEST_F(LoggerTest, StandardOstreamErrorX) {
    Logger clogLogger(std::clog);
    EXPECT_EXIT(
        LLAMA_LOG_ERROR_X(clogLogger, "This is an error message\n"),
        ::testing::ExitedWithCode(1),
        "");
}

// Error message and exit - File ostream
TEST_F(LoggerTest, FileOstreamErrorX) {
    std::ofstream logfile("log", std::ofstream::out | std::ofstream::app);
    Logger fileLogger(logfile);
    EXPECT_EXIT(
        LLAMA_LOG_ERROR_X(fileLogger, "This is an error message, and this line goes into a file\n"),
        ::testing::ExitedWithCode(1),
        "");
    logfile.close();
}

// Error message and exit - Custom ostream
TEST_F(LoggerTest, CustomOstreamErrorX) {
    MyStream stream;
    LoggerWrapper<MyStream> myLogger(stream);
    EXPECT_EXIT(
        LLAMA_LOG_ERROR_X(myLogger, "This is an error message, and this line goes through MyStream\n"),
        ::testing::ExitedWithCode(1),
        "");
}
