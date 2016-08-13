#!/bin/bash

BASEDIR=$(dirname "$0")

cd $BASEDIR/google_benchmark

if [ ! -f CMakeLists.txt ]; then
    git submodule init
    git submodule update
fi

cd ../../../../

if [ ! -f "build_cpp_benchmark/src/libbenchmark.a" ]; then
    mkdir -p build_cpp_benchmark
    cd build_cpp_benchmark
    cmake -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_LTO=true -DBENCHMARK_ENABLE_TESTING=false ../Project-Llama/llama_cpp/benchmark/google_benchmark
    make
    echo "Google benchmark library install complete."
else
    echo "Google benchmark library already installed."
fi
