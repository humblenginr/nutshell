#!/bin/bash

# Compiler flags
CFLAGS=" -Wno-implicit-function-declaration -O0 -g"

set -xe


compile () {
    flex nutsh.l &&
    bison -d nutsh.y && 
    clang $CFLAGS -o nutsh nutsh.tab.c lex.yy.c
}

clear () {
    rm -rf nutsh.tab.c nutsh.tab.h lex.yy.c nutsh
}

if [ "$1" == "compile" ]; then
    compile
elif [ "$1" == "clear" ]; then
    clear
else
    echo "Usage: $0 {compile|clear}"
    exit 1
fi

