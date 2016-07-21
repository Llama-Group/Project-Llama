#!/bin/sh

BASEDIR=$(dirname "$0")

#Go to directory that holds the script file
cd $BASEDIR

# Create build folder
mkdir -p ../build_llama_cpp

# Generate makefile using cmake
cd ../build_llama_cpp
cmake ../Project-Llama/llama_cpp

# Make
make

echo "Build finished."
