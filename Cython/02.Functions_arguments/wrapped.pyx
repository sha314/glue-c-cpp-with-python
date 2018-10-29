# distutils: language = c++
# cython: language_level=3


cimport cython
from libcpp.vector cimport vector

# This file shows 2 examples:
#   - Wrapping an external c function into python, "py_hello"
#   - Wrapping an external c function into python, "py_factorial"


cdef extern from "src/cfunc.h":
	# Imports definitions from a c header file
	# Corresponding source file (cfunc.cpp) must be added to
	# the extension definition in setup.py for proper compiling & linking

	#int factorial(int a)
	float factorial(float a)
	void view_array(vector[int]& v)
	void view_array_2d(vector[vector[int]]& v)

def py_factorial(n):
	# exposes a c function to python
	print("executing py_factorial")
	return factorial(n)

def py_view_array(v):
	print('executing py_view_array')
	view_array(v)

def	py_view_array_2d(v):
	print('executing py_view_array_2d')
	view_array_2d(v)