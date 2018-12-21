#! /usr/bin/env python

# System imports
from distutils.core import *
from distutils      import sysconfig

from setuptools import setup, Extension
from Cython.Distutils import build_ext
import os

os.environ["CC"] = "gcc"
os.environ["CXX"] = "g++"


# Third-party modules - we depend on numpy for everything
import numpy

# Obtain the numpy include directory.  This logic works across numpy versions.
try:
    numpy_include = numpy.get_include()
except AttributeError:
    numpy_include = numpy.get_numpy_include()

# crop extension module
_statmechtools = Extension("_statmechtools",
                   ["convolution.i","convolution.cpp"],
                   include_dirs = [numpy_include],
                   extra_compile_args = ["--verbose", "-std=c++11", "-fopenmp"],
                  libraries=[],
                  language="c++",  # so that the compiler knows about the language
                  extra_link_args=["-std=c++11"]
                   )

# NumyTypemapTests setup
setup(  name        = "Statistical Mechanics Tools",
        description = "A program to compute convolution of data",
        author      = "M. S. Rahman",
        author_email= "shahnoor3pl@gmail.com",
        version     = "1.0",
        ext_modules = [_statmechtools]
        )