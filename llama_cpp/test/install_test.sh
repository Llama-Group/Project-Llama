#!/bin/bash

set -e

BASEDIR=$(dirname "$0")

cd $BASEDIR/google_test
if [ ! -f CMakeLists.txt ]; then
    git submodule init
    git submodule update
fi

cd ../../../../

mkdir -p google_test
cd google_test

if [ -f googlemock/gtest/libgtest.a ]; then
    echo "Found libgtest.a"
    exit 0
fi

cmake ../Project-Llama/llama_cpp/test/google_test/

make

