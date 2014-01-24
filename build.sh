#!/bin/sh
# This is just a convenience script to build and install using cmake.

# default installation prefix when compiling from source
PREFIX=/usr/local
BUILD_TYPE=Release
# alternate prefix when installing in main system
#PREFIX=/usr
# developer prefix for testing
PREFIX=../dist
BUILD_TYPE=Debug

mkdir -p bld
cd bld || exit 1
cmake -DCMAKE_INSTALL_PREFIX=$PREFIX -DCMAKE_BUILD_TYPE=$BUILD_TYPE .. || exit 1
make || exit 1
# you will require sudo to make the application root owned with setuid bit set
sudo make install

