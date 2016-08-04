#!/bin/bash

BASEDIR=$(dirname "$0")

cd $BASEDIR/../llama_cpp

# Change tab to 4 spaces.
find . \( -path "./benchmark/google_benchmark" \) -prune -o -name '*.h' ! -type d -exec bash -c 'expand -t 4 "$0" > /tmp/e && mv /tmp/e "$0"' {} \;

# Remove lines end with whitespaces.
find . \( -path "./benchmark/google_benchmark" \) -prune -o -name '*.h' ! -type d -exec bash -c 'sed 's/[[:blank:]]*$//' "$0">"$0"' {} \;

# Run lint.
find . \( -path "./benchmark/google_benchmark" \) -prune -o -name '*.h' ! -type d -exec bash -c '../lint/google_lint/cpplint/cpplint.py --linelength=120 "$0"' {} \;
