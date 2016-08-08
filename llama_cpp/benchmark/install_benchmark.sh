#!/bin/bash

BASEDIR=$(dirname "$0")

cd $BASEDIR/../../../

if [ ! -f "benchmark_llama_cpp/src/libbenchmark.a" ]; then
    mkdir -p benchmark_llama_cpp
    cd benchmark_llama_cpp
    cmake -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_LTO=true -DBENCHMARK_ENABLE_TESTING=false ../Project-Llama/llama_cpp/benchmark/google_benchmark
    make
    echo "Google benchmark library install complete."
else
    echo "Google benchmark library installed."
fi
