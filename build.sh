#!/bin/bash

# Compiler flags
CFLAGS=" -Wno-implicit-function-declaration -O0 -g"
set -xe


compile () {
    flex nutsh.l &&
    bison -d nutsh.y && 
    clang $CFLAGS -o  nutsh nutsh.tab.c lex.yy.c command.c 
}

run () {
    ./nutsh     
}

compile &&
run
