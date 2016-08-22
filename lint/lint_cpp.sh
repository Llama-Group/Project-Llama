#!/bin/bash

BASEDIR=$(dirname "$0")

cd $BASEDIR/google_lint

if [ ! -d cpplint ]; then
    git submodule init
    git submodule update
fi

cd ../../llama_cpp

export pig="
         ___
         ',_\`\"\"\\        .---,
            \\   :-\"\"\`\`/\`    |
             \`;'     //\`\\   /
             /   __     |   ('.
            |_ ./O)\\     \\  \`) \\
           _/-.    \`      \`\"\`  |\`-.
       .-=; \`                  /   \`-.
      /o o \\   ,_,           .        '.
      L._._;_.-'           .            \`'-.
        \`'-.\`             '                 \`'-.
            \`.         '                        \`-._
              '-._. -'                              '.
                 \\                                    \`\\
                  |                                     \\
                  |    |                                 ;   _.
                  \\    |           |                     |-.((
                   ;.  \\           /    /                |-.\`\\)
                   | '. ;         /    |                 |(_) )
                   |   \\ \\       /\`    |                 ;'--'
                    \\   '.\\    /\`      |                /
                     |   /\`|  ;        \\               /
                     |  |  |  |-._      '.           .'
                     /  |  |  |__.\`'---\"_;'-.     .-'
                    //__/  /  |    .-'\`\`     _.-'\`
                          //__/   //___.--''\`"

export pigSuccess="
     \\_/-\\_/
      )   (
     (     )
      )   (
     /     \\
    (   9   )
   (_\\_____/_)"

## DO NOT RUN UNDER PROJECT FOLDER AS IT MAY CORRUPT .git

# Change tab to 4 spaces.
find . \( -path "./benchmark/google_benchmark" -or -path "./test/google_test" \) -prune -o \( -name "*.h" -or -name "*.cpp" \) ! -type d -exec bash -c 'expand -t 4 "$0" > /tmp/e && mv /tmp/e "$0"' {} \;

# Remove lines end with whitespaces.
find . \( -path "./benchmark/google_benchmark" -or -path "./test/google_test" \) -prune -o \( -name "*.h" -or -name "*.cpp" \) ! -type d -exec bash -c 'sed "s/[[:blank:]]*$//" "$0" > /tmp/e && mv /tmp/e "$0"' {} \;

# Run lint.
rm -f /tmp/llama_fail
find . \( -path "./benchmark" -or -path "./test/google_test" \) -prune -o \( -name "*.h" -or -name "*.cpp" \) ! -type d -exec bash -c '../lint/google_lint/cpplint/cpplint.py --linelength=120 --filter=-build/c++11 "$0";if [ $? != 0 ]; then echo > /tmp/llama_fail; fi' {} \;

echo $retVal
if [ -f /tmp/llama_fail ]; then
    rm /tmp/llama_fail
    echo "$pig"
    echo
    echo "!!! You have some style error! Please follow google style guide! !!!"
    echo "!!!      Do * NOT * push before you fixed these style error!     !!!"
    exit -1
else
    echo "$pigSuccess"
    echo
    echo "==               Oink! Oink!                =="
    echo "== Very Nice, all code style checks passed! =="
fi
