#!/bin/bash

# building
echo ...................................................
echo building

#/usr/bin/python3 setup.py build_ext --inplace
python3 setup.py build_ext --inplace

echo ...................................................
echo removing .c and .cpp file created while compiling
#rm wrapped.cpp
#rm wrapped.c

echo ...................................................
echo testing
# running 'test.py' the build
#/usr/bin/python3 test.py
python3 test.py


