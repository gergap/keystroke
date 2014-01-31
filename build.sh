#!/bin/sh
# This is just a convenience script to build and install using cmake.
# Usage:
# Default build: ./build.sh
# Developer build: ./build.sh dev

# default installation prefix when compiling from source
PREFIX=/usr/local
BUILD_TYPE=Release
# alternate prefix when installing in main system
#PREFIX=/usr
# developer prefix for testing
if [ $# -gt 0 ] && [ "$1" == "dev" ]; then
    PREFIX=$PWD/dist
    BUILD_TYPE=Debug
fi
BLD_DIR=bld

echo "Building in $BUILD_TYPE mode, install location is $PREFIX."
echo "Press Enter to continue."
read

mkdir -p $BLD_DIR
cd $BLD_DIR || exit 1
cmake -DCMAKE_INSTALL_PREFIX=$PREFIX -DCMAKE_BUILD_TYPE=$BUILD_TYPE .. || exit 1
make || exit 1
# you will require sudo to make the application root owned with setuid bit set
sudo make install

