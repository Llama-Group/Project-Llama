
cmake_minimum_required (VERSION 2.8)

project (llama_cpp)

# Check for C++11 and set

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../lib_llama_cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin_llama_cpp")
set(CMAKE_SOURCE_DIR "./src")

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/*.cpp)

add_library(Llama ${SRC_FILES})
