#!/bin/bash

set -e

BASEDIR=$(dirname "$0")

#Go to project directory
cd $BASEDIR/../

if [ "$1" == "" ]; then
	# Create build folder
	rm -rf ../build_llama_cpp
	mkdir -p ../build_llama_cpp
	cd ../build_llama_cpp
	
	# Build library
	cmake ../Project-Llama/llama_cpp
elif [ "$1" == "Xcode" ]; then
	# Create Xcode project folder
	rm -rf ../llama_xcode
	mkdir -p ../llama_xcode
	cd ../llama_xcode
	
	# Generate Xcode Project
	cmake -G Xcode ../Project-Llama/llama_cpp
else
	# Create build folder
	rm -rf ../build_llama_cpp
	mkdir -p ../build_llama_cpp
	cd ../build_llama_cpp
	
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
		case `uname` in 
			Darwin*) echo "			Xcode" ;;
			**) ;;
		esac
		exit -1
	fi
fi

# Make / Build
if [ "$1" == "Xcode" ]; then
	case `uname` in 
		Darwin*) xcodebuild && open ./;;
		**) echo "Xcode Project generated at ../llama_xcode/llama_cpp.xcodeproj" ;;
	esac
else
	make
fi

if [ $? != 0 ]; then
	echo "Failed to make."
	exit -3
else
	echo "Build finished."
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
