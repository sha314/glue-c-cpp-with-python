cimport cython


# This file shows 2 examples:
#   - Wrapping an external c function into python, "py_hello"
#   - Wrapping an external c function into python, "py_factorial"


cdef extern from "src/cfunc.h":
    # Imports definitions from a c header file
    # Corresponding source file (cfunc.cpp) must be added to
    # the extension definition in setup.py for proper compiling & linking

    void hello()
    int factorial(int a)

def py_hello():
    # Exposes a c function to python
    print('executing py_hello')
    hello()
    pass
    

def py_factorial(n):
    # exposes a c function to python
    print("executing py_factorial")
    return factorial(n)