
cmake_minimum_required (VERSION 2.8)

project (test_build)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../lib_llama_cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin_llama_cpp")
set(CMAKE_SOURCE_DIR "../../src")

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/*.cpp)

add_executable(test_build ${SRC_FILES} test_build.cpp)
