# SWIG, Numpy, C++ 

https://docs.scipy.org/doc/numpy-1.13.0/reference/swig.interface-file.html

https://scipy-cookbook.readthedocs.io/items/SWIG_NumPy_examples.html

https://stackoverflow.com/questions/16377503/use-swig-to-wrap-c-vector-as-python-numpy-array

https://scipy-cookbook.readthedocs.io/items/SWIG_Memory_Deallocation.html


# Pointer
if pointer or reference for an array is needed use naked array.



use of vector and then converting it to a pointer by taing the address of the
first element for return value leads to error since python also tries to 
free up memories that are already freed by vector. solution : use naked array
in such case.

