
cmake_minimum_required (VERSION 2.8)

project (llama_cpp)

ENABLE_TESTING()

#
# Checking environment
#

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
if(COMPILER_SUPPORTS_CXX1Z)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
    set(COVERAGE_FLAGS "-std=c++1z -g -O0 -fprofile-arcs -ftest-coverage")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(COVERAGE_FLAGS "-std=c++11 -g -O0 -fprofile-arcs -ftest-coverage")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    set(COVERAGE_FLAGS "-std=c++0x -g -O0 -fprofile-arcs -ftest-coverage")
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
include_directories("${PROJECT_ROOT_DIRECTORY}/llama_cpp/test/google_test/googletest/include/")

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/*.h)

set(PROJECT_EXAMPLE_DIRECTORY "${PROJECT_ROOT_DIRECTORY}/llama_cpp/example")
set(PROJECT_BENCHMARK_DIRECTORY "${PROJECT_ROOT_DIRECTORY}/llama_cpp/benchmark")
set(PROJECT_TEST_DIRECTORY "${PROJECT_ROOT_DIRECTORY}/llama_cpp/test")

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

# Google test
set(GOOGLE_TEST "${PROJECT_ROOT_DIRECTORY}/../google_test/googlemock/gtest/libgtest.a")

# pthread
find_package(Threads)

#
# Build targets
#

list(APPEND SOURCE_LIBRARIES "${CRYPTO_LIBRARIES}")
list(APPEND TEST_LIBRARIES "-lz ${PROJECT_ROOT_DIRECTORY}/../google_test/googlemock/gtest/libgtest.a" ${CMAKE_THREAD_LIBS_INIT})
list(APPEND BIN_LIBRARIES "-lz ${PROJECT_ROOT_DIRECTORY}/../build_llama_cpp/libllama.a")
list(APPEND BENCHMARK_LIBRARIES "${GOOGLE_BENCHMARK}" ${CMAKE_THREAD_LIBS_INIT})

# Library
if( CMAKE_BUILD_TYPE STREQUAL "Coverage" )
    include(${CMAKE_SOURCE_DIR}/../CodeCoverage.cmake)

    set(TEMP_CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(TEMP_CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    set(TEMP_CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})
    
    set(CMAKE_CXX_FLAGS "${COVERAGE_FLAGS}")
    set(CMAKE_C_FLAGS "${COVERAGE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS ${COVERAGE_FLAGS})

    message("[+L] Will build llama library for coverage")
    add_library(llama ${SOURCE_FILES})
    target_link_libraries(llama ${SOURCE_LIBRARIES})
    add_custom_command(
        TARGET llama
        WORKING_DIRECTORY ${PROJECT_ROOT_DIRECTORY}/..
        COMMAND if [ -d ./xcode_llama/Debug ]\; then cp ./xcode_llama/Debug/libllama.a ./build_llama_cpp/\; fi
    )

    set(CMAKE_CXX_FLAGS "${TEMP_CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${TEMP_CMAKE_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS ${TEMP_CMAKE_EXE_LINKER_FLAGS})
else()
    message("[+L] Will build llama library")
    add_library(llama ${SOURCE_FILES})
    target_link_libraries(llama ${SOURCE_LIBRARIES})
    add_custom_command(
        TARGET llama
        WORKING_DIRECTORY ${PROJECT_ROOT_DIRECTORY}/..
        COMMAND if [ -d ./xcode_llama/Debug ]\; then cp ./xcode_llama/Debug/libllama.a ./build_llama_cpp/\; fi
    )
endif()

# Unit Test
macro(BuildUnitTest FOLDER_NAME)
    if(NOT ${FOLDER_NAME} STREQUAL "")
        message("[+T] Will build ${FOLDER_NAME} unit test")
        include_directories(${PROJECT_TEST_DIRECTORY}/${FOLDER_NAME}/)
        file(GLOB_RECURSE TEMP_TARGET_SOURCE_FILES ${PROJECT_TEST_DIRECTORY}/${FOLDER_NAME}/*.cpp)
        add_executable(${FOLDER_NAME} ${TEMP_TARGET_SOURCE_FILES})
        add_dependencies(${FOLDER_NAME} llama)
        target_link_libraries(${FOLDER_NAME} ${BIN_LIBRARIES} ${TEST_LIBRARIES} ${SOURCE_LIBRARIES})
        add_test(NAME ${FOLDER_NAME} COMMAND ${FOLDER_NAME})
    endif()
endmacro()

# Examples
macro(BuildExample FOLDER_NAME)
    if(NOT ${FOLDER_NAME} STREQUAL "")
        message("[+E] Will build ${FOLDER_NAME}.")
        include_directories(${PROJECT_EXAMPLE_DIRECTORY}/${FOLDER_NAME}/)
        file(GLOB_RECURSE TEMP_TARGET_SOURCE_FILES ${PROJECT_EXAMPLE_DIRECTORY}/${FOLDER_NAME}/*.cpp)
        add_executable(${FOLDER_NAME} ${TEMP_TARGET_SOURCE_FILES})
        add_dependencies(${FOLDER_NAME} llama)
        target_link_libraries(${FOLDER_NAME} ${BIN_LIBRARIES} ${SOURCE_LIBRARIES})
        message("[+R] Will copy resources of ${FOLDER_NAME} (if any).")
        ADD_CUSTOM_COMMAND(
            TARGET ${FOLDER_NAME}
            COMMAND if [ -d '${PROJECT_EXAMPLE_DIRECTORY}/${FOLDER_NAME}/Resources' ]; then find "${PROJECT_EXAMPLE_DIRECTORY}/${FOLDER_NAME}/Resources/*" -print0 | xargs -0 -I{} cp {} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} \; fi ;
        )
    endif()
endmacro()

# Benchmarks
macro(BuildBenchmark FOLDER_NAME)
    if(NOT ${FOLDER_NAME} STREQUAL "")
        message("[+B] Will build ${FOLDER_NAME}.")
        include_directories(${PROJECT_BENCHMARK_DIRECTORY}/${FOLDER_NAME}/)
        file(GLOB_RECURSE TEMP_TARGET_SOURCE_FILES ${PROJECT_BENCHMARK_DIRECTORY}/${FOLDER_NAME}/*.cpp)
        add_executable(${FOLDER_NAME} ${TEMP_TARGET_SOURCE_FILES})
        add_dependencies(${FOLDER_NAME} llama)
        target_link_libraries(${FOLDER_NAME} ${BIN_LIBRARIES} ${BENCHMARK_LIBRARIES} ${SOURCE_LIBRARIES})
    endif()
endmacro()

# List of building targets
BuildUnitTest("Sort_UnitTest")

BuildExample("${TEST_BUILD}")
BuildExample("${SPAM_CLASSIFICATION}")
BuildExample("${RSA}")
BuildExample("${SORT_TEST}")
BuildExample("${MERSENNE_TWISTER}")
BuildExample("${KMEANS}")
BuildExample("${ALPACA_SORT_TEST}")
BuildExample("${FUNCTOR_TEST}")
BuildExample("${DATA_GENERATOR}")

BuildBenchmark("${SORT_BENCHMARK}")

if( CMAKE_BUILD_TYPE STREQUAL "Coverage" )
    SETUP_TARGET_FOR_COVERAGE(coverage "make test" coverage_report)
endif()
