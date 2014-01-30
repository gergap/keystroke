#!/bin/sh
# This is just a convenience script to build and install using cmake.

# developer prefix for testing
PREFIX=../dist
BUILD_TYPE=Debug
BLD_DIR=bldAnalysis
# use clang static analyzer
export CC=ccc-analyzer
export CXX=ccc-analyzer

rm -rf $BLD_DIR
mkdir $BLD_DIR || exit 1
cd $BLD_DIR || exit 1
cmake -DCMAKE_INSTALL_PREFIX=$PREFIX -DCMAKE_BUILD_TYPE=$BUILD_TYPE .. || exit 1
scan-build make

