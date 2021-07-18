#! /bin/bash

source_dir=$(pwd)

if [ ! -d "build" ]
then
    mkdir build
fi

cd build
cmake ..
make

./test/test

cd $source_dir