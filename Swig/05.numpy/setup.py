#! /usr/bin/env python

# System imports
from distutils.core import *
from distutils      import sysconfig

# Third-party modules - we depend on numpy for everything
import numpy

# Obtain the numpy include directory.  This logic works across numpy versions.
try:
    numpy_include = numpy.get_include()
except AttributeError:
    numpy_include = numpy.get_numpy_include()

# ezrange extension module
_carray = Extension("_carray",
                   ["carray.i","src/myarray.cpp"],
                    libraries=[],
                    include_dirs = [numpy_include],
                    language="c++",  # so that the compiler knows about the language
                    extra_compile_args=["-std=c++11"],
                    extra_link_args=["-std=c++11"]
                   )

# ezrange setup
setup(  name        = "range function",
        description = "range takes an integer and returns an n element int array where each element is equal to its index",
        author      = "Egor Zindy",
        version     = "1.0",
        ext_modules = [_carray]
        )


