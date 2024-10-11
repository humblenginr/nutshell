#!/bin/bash

# Compiler flags
CFLAGS=" -Wno-implicit-function-declaration -O0 -g"
BUILD_DIR=./build

set -xe

clear_build () {
    rm -rf $BUILD_DIR
}

compile () {
    cd $BUILD_DIR &&
    flex ../nutsh.l &&
    bison -d ../nutsh.y && 
    clang $CFLAGS -o nutsh nutsh.tab.c lex.yy.c &&
    cd ../
}

run () {
    $BUILD_DIR/nutsh     
}

mkdir -p $BUILD_DIR &&
compile &&
run
