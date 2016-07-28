
cmake_minimum_required (VERSION 2.8)

project (sort_benchmark)

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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(PROJECT_ROOT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../..") # Change this before change folder of CMakeLists.txt

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_ROOT_DIRECTORY}/../lib_llama_cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_ROOT_DIRECTORY}/../bin_llama_cpp")
set(CMAKE_SOURCE_DIR "${PROJECT_ROOT_DIRECTORY}/llama_cpp/src")

include_directories(${CMAKE_SOURCE_DIR})
include_directories("${PROJECT_ROOT_DIRECTORY}/llama_cpp/benchmark/google_benchmark/include/")

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/*.cpp)

find_package(PkgConfig REQUIRED)
pkg_search_module(CRYPTO REQUIRED libcrypto)

if( CRYPTO_FOUND )
    include_directories(${CRYPTO_INCLUDE_DIRS})
    link_directories(${CRYPTO_LIBRARY_DIRS})
    message(STATUS "Using Crypto ${CRYPTO_VERSION}")
else()
    # Error; with REQUIRED, pkg_search_module() will throw an error by it's own
endif()

find_package (Threads)

set(BENCHMARK_LIBRARY "${PROJECT_ROOT_DIRECTORY}/../benchmark_llama_cpp/src/libbenchmark.a")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lz ${PROJECT_ROOT_DIRECTORY}/../benchmark_llama_cpp/src/libbenchmark.a")

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE EXAMPLE_FILES ./*.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES} ${EXAMPLE_FILES})

link_directories("${PROJECT_ROOT_DIRECTORY}/../benchmark_llama_cpp/src/")
target_link_libraries(${CMAKE_PROJECT_NAME} ${CRYPTO_LIBRARIES} "-lz /usr/local/lib/libbenchmark.a" ${CMAKE_THREAD_LIBS_INIT})
