
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
# Coverage
#

FUNCTION(SETUP_TARGET_FOR_COVERAGE _targetname _testrunner _outputname)

IF(NOT LCOV_PATH)
MESSAGE(FATAL_ERROR "lcov not found! Aborting...")
ENDIF() # NOT LCOV_PATH

IF(NOT GENHTML_PATH)
MESSAGE(FATAL_ERROR "genhtml not found! Aborting...")
ENDIF() # NOT GENHTML_PATH

SET(coverage_info "${CMAKE_BINARY_DIR}/${_outputname}.info")
SET(coverage_cleaned "${coverage_info}.cleaned")

SEPARATE_ARGUMENTS(test_command UNIX_COMMAND "${_testrunner}")

# Setup target
ADD_CUSTOM_TARGET(${_targetname}

# Cleanup lcov
${LCOV_PATH} --directory . --zerocounters

# Run tests
COMMAND ${test_command} ${ARGV3}

# Capturing lcov counters and generating report
COMMAND ${LCOV_PATH} --directory . --capture --output-file ${coverage_info}
COMMAND ${LCOV_PATH} --remove ${coverage_info} 'tests/*' '/usr/*' --output-file ${coverage_cleaned}
COMMAND ${GENHTML_PATH} -o ${_outputname} ${coverage_cleaned}
COMMAND ${CMAKE_COMMAND} -E remove ${coverage_info} ${coverage_cleaned}

WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
COMMENT "Resetting code coverage counters to zero.\nProcessing code coverage counters and generating report."
)

# Show info where to find the report
ADD_CUSTOM_COMMAND(TARGET ${_targetname} POST_BUILD
COMMAND ;
COMMENT "Open ./${_outputname}/index.html in your browser to view the coverage report."
)

ENDFUNCTION()

#
# Setting flags
#

if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "")
	include(${CMAKE_SOURCE_DIR}/../CodeCoverage.cmake)
	set(CMAKE_CXX_FLAGS "${COVERAGE_FLAGS}")
	set(CMAKE_C_FLAGS "${COVERAGE_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS ${COVERAGE_FLAGS})
endif()

#
# Build targets
#

list(APPEND SOURCE_LIBRARIES "${CRYPTO_LIBRARIES}")
list(APPEND BIN_LIBRARIES "-lz ${PROJECT_ROOT_DIRECTORY}/../build_llama_cpp/libllama.a")
list(APPEND BENCHMARK_LIBRARIES "${GOOGLE_BENCHMARK}" ${CMAKE_THREAD_LIBS_INIT})

# Library
message("[+L] Will build llama library")
add_library(llama ${SOURCE_FILES})
target_link_libraries(llama ${SOURCE_LIBRARIES})

# Examples
macro(BuildExample FOLDER_NAME)
	if(NOT ${FOLDER_NAME} STREQUAL "")
		message("[+E] Will build ${FOLDER_NAME}.")
		include_directories(${PROJECT_EXAMPLE_DIRECTORY}/${FOLDER_NAME}/)
		file(GLOB_RECURSE TEMP_TARGET_SOURCE_FILES ${PROJECT_EXAMPLE_DIRECTORY}/${FOLDER_NAME}/*.cpp)
        add_executable(${FOLDER_NAME} ${TEMP_TARGET_SOURCE_FILES})
        add_dependencies(${FOLDER_NAME} llama)
        target_link_libraries(${FOLDER_NAME} ${BIN_LIBRARIES} ${SOURCE_LIBRARIES})
		add_test(NAME ${FOLDER_NAME}_test COMMAND ${FOLDER_NAME})
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
		add_test(NAME ${FOLDER_NAME}_test COMMAND ${FOLDER_NAME})
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

if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "")
	SETUP_TARGET_FOR_COVERAGE(coverage "make test" coverage_report)
endif()
