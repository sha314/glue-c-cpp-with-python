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

# crop extension module
_crop = Extension("_crop",
                   ["crop.i","crop.c"],
                   include_dirs = [numpy_include],
                   extra_compile_args = ["--verbose"]
                   )

# NumyTypemapTests setup
setup(  name        = "crop test",
        description = "A simple crop test to demonstrate the use of ARGOUTVIEWM_ARRAY2",
        author      = "Egor Zindy",
        version     = "1.0",
        ext_modules = [_crop]
        )