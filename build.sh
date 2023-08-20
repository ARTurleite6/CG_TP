#! /usr/bin/bash

if [ $# -eq 0 ]
then
  echo "No arguments supplied"
  exit 1
fi

mkdir build

cd build

if [ $1 = "Release" ] 
then
  cmake -DCMAKE_BUILD_TYPE=Release .. 
  cd ..
else
  cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE .. 
  cd ..
  ln -s build/compile_commands.json
fi

cmake --build build

python3 planets_parser.py

