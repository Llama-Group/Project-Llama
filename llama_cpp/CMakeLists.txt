
cmake_minimum_required (VERSION 2.8)

project (llama_cpp)

# Check for C++11 and set

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
if(COMPILER_SUPPORTS_CXX1Z)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../lib_llama_cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin_llama_cpp")
set(CMAKE_SOURCE_DIR "./src")

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/*.cpp)

find_package(PkgConfig REQUIRED)
pkg_search_module(CRYPTO REQUIRED libcrypto)

if( CRYPTO_FOUND )
    include_directories(${CRYPTO_INCLUDE_DIRS})
    message(STATUS "Using Crypto ${CRYPTO_VERSION}")
else()
    # Error; with REQUIRED, pkg_search_module() will throw an error by it's own
endif()

add_library(Llama ${SRC_FILES})

target_link_libraries(Llama ${CRYPTO_LIBRARIES})