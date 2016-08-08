#!/bin/bash

set -e

BASEDIR=$(dirname "$0")

#Go to project directory
cd $BASEDIR/../

if [ "$1" == "" ]; then
	# Create build folder
	rm -rf ../build_llama_cpp
	mkdir -p ../build_llama_cpp
	pushd ../build_llama_cpp >> /dev/null
	
	# Build library
	cmake ../Project-Llama/llama_cpp
	popd >> /dev/null
elif [ "$1" == "Xcode" ]; then
	# Create Xcode project folder
	rm -rf ../llama_xcode
	mkdir -p ../llama_xcode
	pushd ../llama_xcode >> /dev/null
	
	# Generate Xcode Project
	cmake -G Xcode ../Project-Llama/llama_cpp
	popd >> /dev/null
else
	# Create build folder
	rm -rf ../build_llama_cpp
	mkdir -p ../build_llama_cpp
	pushd ../build_llama_cpp >> /dev/null
	
	# Build examples
	if [ "$1" == "-e" ] || [ "$1" == "--example" ] && [ "$2" != "" ]; then
		if [ -d "../Project-Llama/llama_cpp/example/"$2 ]; then
			echo "Building: Project-Llama/llama_cpp/example/"$2
			cmake -D$(echo $2 | awk '{print toupper($0)}')=$2 ../Project-Llama/llama_cpp/
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
			cmake -D$(echo $2 | awk '{print toupper($0)}')=$2 ../Project-Llama/llama_cpp/
		else
			echo "No such benchmark."
			ext -4
		fi
	elif [ "$1" == "all" ]; then
		../Project-Llama/llama_cpp/benchmark/install_benchmark.sh
		if [ $? != 0 ]; then
			echo "Failed to build Google Benchmark"
			exit -5
		fi
		flag=" "
		if [ "$2" == "coverage" ]; then
			flags=$flags"-DCMAKE_BUILD_TYPE=Coverage "
		fi
		flags=$flags
		pushd ../Project-Llama/llama_cpp/example >> /dev/null
		target=($(ls -d */))
		popd >> /dev/null
		pushd ../Project-Llama/llama_cpp/benchmark  >>/dev/null
		targetb=($(echo $(ls -d */) | awk '{gsub("google_benchmark/ ", "");print}'))
		target=("${target[@]}" "${targetb[@]}")
		popd >> /dev/null
		for i in "${target[@]////}"; do
			flags=$flags\ -D$(echo $i | awk '{print toupper($0)}')=$i
		done
		cmake $flags ../Project-Llama/llama_cpp/
	else
		echo "Usage: ./build_cpp.sh 	[-e|--example] [example name]|all"
		echo "			[-b|--benchmark] [benchmark name]|all"
		if [ "$(uname -s)" == "Darwin" ]; then
			echo "			Xcode"
		fi
		exit -1
	fi
fi

# Make / Build
if [ "$1" == "Xcode" ]; then
	pushd ../build_llama_cpp >> /dev/null
	if [ "$(uname -s)" == "Darwin" ]; then
		xcodebuild
		if [ $? != 0 ]; then
			echo "Failed to do xcodebuild."
			exit -3
		else
			echo "Build finished."
			open ./
		fi
	else
		echo "Xcode Project generated at ../llama_xcode/llama_cpp.xcodeproj"
	fi
	popd >> /dev/null
else
	make
	if [ $? != 0 ]; then
		echo "Failed to make."
		exit -3
	else
		echo "Build finished."
	fi
fi

if [ "$2" == "coverage" ]; then
	make coverage
    tput setaf 2
    echo "Coverage report generated: $(pwd)coverage_report/index.html"
    tput sgr0
    if [ "$(uname -s)" == "Darwin" ]; then
        open ./coverage_report/index.html
    fi
else
    # Lint
    echo "Checking code style."
    ../Project-Llama/lint/lint_cpp.sh
fi
