
cmake_minimum_required (VERSION 2.8)

project (llama_cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin_llama_cpp")

add_executable(test_build test_build.cpp)
