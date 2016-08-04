#!/bin/bash

BASEDIR=$(dirname "$0")

cd $BASEDIR/../llama_cpp

find ./ \( -path "./benchmark/google_benchmark" \) -prune -o -name '*.cpp' -o -name '*.h' ! -type d -exec bash -c 'expand -t 4 "$0" > /tmp/e && mv /tmp/e "$0"' {} \;

find ./ \( -path "./benchmark/google_benchmark" \) -prune -o -name '*.cpp' -o -name '*.h' ! -type d -exec bash -c '../lint/google_lint/cpplint/cpplint.py "$0"' {} \;
