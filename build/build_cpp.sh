#!/bin/bash

BASEDIR=$(dirname "$0")

#Go to project directory
cd $BASEDIR/../

# Create build folder
rm -rf ../build_llama_cpp
mkdir -p ../build_llama_cpp
cd ../build_llama_cpp

if [ "$1" == "" ]; then
	# Build library
	cmake ../Project-Llama/llama_cpp
else
	# Build examples
	if [ "$1" == "-e" ] || [ "$1" == "--example" ] && [ "$2" != "" ]; then
		if [ -d "../Project-Llama/llama_cpp/example/"$2 ]; then
			echo "Building: Project-Llama/llama_cpp/example/"$2
			cmake ../Project-Llama/llama_cpp/example/$2
		else
			echo "No such example."
			exit -2
		fi
	elif [ "$1" == "-b" ] || [ "$1" == "--benchmark" ]; then
		../Project-Llama/llama_cpp/benchmark/install_benchmark.sh
		if [ $? != 0 ]; then
			echo "Failed to build Google Benchmark"
			exit -5
		fi
		if [ -d "../Project-Llama/llama_cpp/benchmark/"$2 ]; then
			echo "Building: Project-Llama/llama_cpp/benchmark/"$2
			cmake -DCMAKE_CXX_COMPILER="clang++"../Project-Llama/llama_cpp/benchmark/$2
		else
			echo "No such benchmark."
			ext -4
		fi
	else
		echo "Usage: ./build_cpp.sh 	[-e|--example] [example name]"
		echo "			[-b|--benchmark] [benchmark name]"
		exit -1
	fi
fi

# Make
make
if [ $? != 0 ]; then
	echo "Failed to make."
	exit -3
else
	echo "Build finished."
fi
