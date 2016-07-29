
cmake_minimum_required (VERSION 2.8)

project (llama_cpp)

#
# Checking environment
#

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
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

#
# Setting variables
#

set(PROJECT_ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_ROOT_DIRECTORY}/../lib_llama_cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_ROOT_DIRECTORY}/../bin_llama_cpp")
set(CMAKE_SOURCE_DIR "${PROJECT_ROOT_DIRECTORY}/llama_cpp/src")

include_directories("${CMAKE_SOURCE_DIR}/")
include_directories("${PROJECT_ROOT_DIRECTORY}/llama_cpp/benchmark/google_benchmark/include/")

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/*.cpp)

set(PROJECT_EXAMPLE_DIRECTORY "${PROJECT_ROOT_DIRECTORY}/llama_cpp/example")
set(PROJECT_BENCHMARK_DIRECTORY "${PROJECT_ROOT_DIRECTORY}/llama_cpp/benchmark")

#
# Preparing libraries
#

# OpenSSL
find_package(PkgConfig REQUIRED)
pkg_search_module(CRYPTO REQUIRED libcrypto)

if(CRYPTO_FOUND)
    include_directories(${CRYPTO_INCLUDE_DIRS})
    message(STATUS "Using Crypto ${CRYPTO_VERSION}")
else()
    # Error; with REQUIRED, pkg_search_module() will throw an error by it's own
endif()

# Google benchmark
set(GOOGLE_BENCHMARK "${PROJECT_ROOT_DIRECTORY}/../benchmark_llama_cpp/src/libbenchmark.a")

# pthread
find_package(Threads)

#
# Build targets
#

list(APPEND SOURCE_LIBRARIES "${CRYPTO_LIBRARIES}")
list(APPEND BENCHMARK_LIBRARIES "${GOOGLE_BENCHMARK}" ${CMAKE_THREAD_LIBS_INIT})

# Library
if(NOT "${LIBLLAMA}" STREQUAL "")
	message("[L-L] Will build llama library")
	add_library(llama ${SOURCE_FILES})
	target_link_libraries(llama ${SOURCE_LIBRARIES})
endif()

# Examples
macro(BuildExample FOLDER_NAME)
	if(NOT ${FOLDER_NAME} STREQUAL "")
		message("[L-E] Will build ${FOLDER_NAME}.")
		include_directories(${PROJECT_EXAMPLE_DIRECTORY}/${FOLDER_NAME}/)
		file(GLOB_RECURSE TEMP_TARGET_SOURCE_FILES ${PROJECT_EXAMPLE_DIRECTORY}/${FOLDER_NAME}/*.cpp)
		add_executable(${FOLDER_NAME} ${SOURCE_FILES} ${TEMP_TARGET_SOURCE_FILES})
		target_link_libraries(${FOLDER_NAME} ${SOURCE_LIBRARIES})
	endif()
endmacro()

# Benchmarks
macro(BuildBenchmark FOLDER_NAME)
	if(NOT ${FOLDER_NAME} STREQUAL "")
		message("[L-B] Will build ${FOLDER_NAME}.")
		include_directories(${PROJECT_BENCHMARK_DIRECTORY}/${FOLDER_NAME}/)
		file(GLOB_RECURSE TEMP_TARGET_SOURCE_FILES ${PROJECT_BENCHMARK_DIRECTORY}/${FOLDER_NAME}/*.cpp)
		add_executable(${FOLDER_NAME} ${SOURCE_FILES} ${TEMP_TARGET_SOURCE_FILES})
		target_link_libraries(${FOLDER_NAME} ${BENCHMARK_LIBRARIES} ${SOURCE_LIBRARIES})
	endif()
endmacro()

# List of building targets
BuildExample("${TEST_BUILD}")
BuildExample("${SPAM_CLASSIFICATION}")
BuildExample("${RSA}")
BuildExample("${SORT_TEST}")
BuildExample("${MERSENNE_TWISTER}")
BuildExample("${KMEANS}")
BuildExample("${ALPACA_SORT_TEST}")

BuildBenchmark("${SORT_BENCHMARK}")
