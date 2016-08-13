#!/bin/bash

set -e

BASEDIR=$(dirname "$0")

#Go to project directory
cd "$BASEDIR"/../

if [ ! -d ../Project-Llama ]; then
    echo "Project name must be Project-Llama!"
    exit -6
fi

# Create build folder
rm -rf ../build_llama_cpp
mkdir -p ../build_llama_cpp
cd ../build_llama_cpp

CMAKEFLAGS=""

# Build Google Test
../Project-Llama/llama_cpp/test/install_test.sh

if [ "$1" == "" ]; then
    # Build library
    cmake ../Project-Llama/llama_cpp
else
    # Build examples
    if [ "$1" == "-e" ] || [ "$1" == "--example" ] && [ "$2" != "" ]; then
        if [ -d "../Project-Llama/llama_cpp/example/""$2" ]; then
            echo "Building: Project-Llama/llama_cpp/example/""$2"
            CMAKEFLAGS=-D$(echo "$2" | awk '{print toupper($0)}')="$2"
            if [ "$3" == "xcode" ]; then
                CMAKEFLAGS+=" -G Xcode"
            fi
        else
            echo "No such example."
            exit -2
        fi
    # Build benchmarks
    elif [ "$1" == "-b" ] || [ "$1" == "--benchmark" ]; then
        ../Project-Llama/llama_cpp/benchmark/install_benchmark.sh
        if [ $? != 0 ]; then
            echo "Failed to build Google Benchmark"
            exit -5
        fi
        if [ -d "../Project-Llama/llama_cpp/benchmark/""$2" ]; then
            echo "Building: Project-Llama/llama_cpp/benchmark/""$2"
            CMAKEFLAGS=-D$(echo "$2" | awk '{print toupper($0)}')="$2"
            if [ "$3" == "xcode" ]; then
                CMAKEFLAGS+=" -G Xcode"
            fi
        else
            echo "No such benchmark."
            exit -4
        fi
    # Build all
    elif [ "$1" == "all" ]; then
        ../Project-Llama/llama_cpp/benchmark/install_benchmark.sh
        if [ $? != 0 ]; then
            echo "Failed to build Google Benchmark"
            exit -5
        fi
        flags=""
        flags=$flags
        pushd ../Project-Llama/llama_cpp/example >> /dev/null
        target=($(ls -d */))
        popd >> /dev/null
        pushd ../Project-Llama/llama_cpp/benchmark  >>/dev/null
        targetb=($(ls -d */ | awk '{gsub("google_benchmark/ ", "");print}'))
        target=("${target[@]}" "${targetb[@]}")
        popd >> /dev/null
        for i in "${target[@]////}"; do
            flags=$flags\ -D$(echo "$i" | awk '{print toupper($0)}')="$i"
        done
        CMAKEFLAGS="$flags"
        if [ "$2" == "xcode" ]; then
            CMAKEFLAGS+=" -G Xcode"
        fi
    # Build lib coverage
    elif [ "$1" == "coverage" ]; then
        CMAKEFLAGS="-DCMAKE_BUILD_TYPE=Coverage"
    # Show help
    else
        echo "Usage: ./build_cpp.sh  [-e|--example] [example name]|all (xcode)"
        echo "                       [-b|--benchmark] [benchmark name]|all (xcode)"
        echo "                       coverage"

        exit -1
    fi
fi

# Run CMake here
if [ "$CMAKEFLAGS" != "" ]; then
    echo "Building with: $CMAKEFLAGS"
    if [[ $CMAKEFLAGS == *"-G Xcode"* ]]; then
        rm -rf ../xcode_llama
        mkdir -p ../xcode_llama
        pushd ../xcode_llama >> /dev/null
        cmake $CMAKEFLAGS ../Project-Llama/llama_cpp/
        popd >> /dev/null
    else
        cmake $CMAKEFLAGS ../Project-Llama/llama_cpp/
    fi
else
    echo "Invalid CMake command!"
fi

if [[ ! $CMAKEFLAGS == *"-G Xcode"* ]]; then
    # Make
    make
    if [ $? != 0 ]; then
        echo "Failed to make."
        exit -3
    else
        echo "Build finished."
    fi
fi

# Post make
if [ "$1" == "coverage" ]; then
    make coverage
    tput setaf 2
    echo "Coverage report generated: $(pwd)coverage_report/index.html"
    tput sgr0
    if [ "$(uname -s)" == "Darwin" ]; then
        open ./coverage_report/index.html
    fi
elif [[ $CMAKEFLAGS == *"-G Xcode"* ]]; then
    if [ "$(uname -s)" == "Darwin" ]; then
        echo "Xcode project generated."
        open ../xcode_llama
    fi
else
    # Lint
    echo "Checking code style."
    ../Project-Llama/lint/lint_cpp.sh
fi

