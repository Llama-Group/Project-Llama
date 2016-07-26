
cmake_minimum_required (VERSION 2.8)

project (rsa)

# Check for C++11 and set

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
if(COMPILER_SUPPORTS_CXX1Z)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
elseif(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../lib_llama_cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin_llama_cpp")
set(CMAKE_SOURCE_DIR "../../src")

include_directories(${CMAKE_SOURCE_DIR})

find_package(PkgConfig REQUIRED)
pkg_search_module(CRYPTO REQUIRED libcrypto)

if( CRYPTO_FOUND )
    include_directories(${CRYPTO_INCLUDE_DIRS})
    link_directories(${CRYPTO_LIBRARY_DIRS})
    message(STATUS "Using Crypto ${CRYPTO_VERSION}")
else()
    # Error; with REQUIRED, pkg_search_module() will throw an error by it's own
endif()

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE EXAMPLE_FILES ./*.cpp)

add_executable(rsa ${SRC_FILES} ${EXAMPLE_FILES})

target_link_libraries(rsa ${CRYPTO_LIBRARIES})
