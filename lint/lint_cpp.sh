#!/bin/bash

BASEDIR=$(dirname "$0")

cd $BASEDIR/../llama_cpp/

for i in `find ./ -name "*.cpp" -o -name "*.h" -o -name "*.hpp"` ; do ../lint/google_lint/cpplint/cpplint.py $i ;  done
