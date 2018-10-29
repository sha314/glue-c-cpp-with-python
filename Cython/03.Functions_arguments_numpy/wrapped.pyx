# distutils: language = c++
# cython: language_level=3

# tag: numpy_old
# You can ignore the previous line.
# It's for internal testing of the cython documentation.

import numpy as np

# # "cimport" is used to import special compile-time information
# # about the numpy module (this is stored in a file numpy.pxd which is
# # currently part of the Cython distribution).
# cimport numpy as cnp

# # We now need to fix a datatype for our arrays. I've used the variable
# # DTYPE for this, which is assigned to the usual NumPy runtime
# # type info object.
# DTYPE = np.int

# # "ctypedef" assigns a corresponding compile-time type to DTYPE_t. For
# # every type in the numpy module there's a corresponding compile-time
# # type with a _t-suffix.
# ctypedef np.int_t DTYPE_t



from libcpp.vector cimport vector

# This file shows 2 examples:
#   - Wrapping an external c function into python, "py_hello"
#   - Wrapping an external c function into python, "py_factorial"


cdef extern from "src/cfunc.h":
	# Imports definitions from a c header file
	# Corresponding source file (cfunc.cpp) must be added to
	# the extension definition in setup.py for proper compiling & linking

	void view_array(vector[int]& v)
	void view_array_2d(vector[vector[int]]& v)
	vector[int] add(vector[int]& v1, vector[int]& v2)

	vector[vector[double]]	mat_mul(vector[vector[double]]& mat1, vector[vector[double]]& mat2)

def py_view_array(v):
	print('executing py_view_array')
	view_array(v)

def	py_view_array_2d(v):
	print('executing py_view_array_2d')
	view_array_2d(v)

def py_add(v1, v2):
	print("executing py_add")
	if isinstance(v1, list):
		return add(v1, v2)
	if isinstance(v1, np.ndarray):
		return np.array(add(v1, v2))

def py_mat_mul(A, B):
	if A.shape[1] != B.shape[0]:
		print("error is going to happen")
		pass
	C = mat_mul(A, B)
	return np.array(C)



