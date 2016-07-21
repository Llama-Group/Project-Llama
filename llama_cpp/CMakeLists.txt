
cmake_minimum_required (VERSION 3.1)

project (llama_cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin_llama_cpp")

add_executable(test_build test_build.cpp)
