#!/bin/bash
# to compile in python 3

echo --------------------------------------------------
echo building

/usr/bin/python3 setup.py build_ext --inplace

echo --------------------------------------------------
echo testing

/usr/bin/python3 test.py

