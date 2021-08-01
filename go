#! /bin/bash

source_dir=$(pwd)

if [ ! -d "build" ]
then
    mkdir build
fi

cd build
cmake ..
make

if [ $? -eq 0 ]; then
   ./test/test
else
   echo Build Failed...
fi


cd $source_dir