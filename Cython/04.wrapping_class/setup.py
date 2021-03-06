
from setuptools import setup, Extension
from Cython.Distutils import build_ext
import numpy as np

NAME = "rectangleapp"
VERSION = "0.1"
DESCR = "shows how to wrap C/C++ code into python using Cython"
URL = ""
REQUIRES = ['cython']

AUTHOR = "M.S. Rahman"
EMAIL = "shahnoor3pl@gmail.com"

LICENSE = ""

SRC_DIR = "."  # source file directory
out_extension_directory = '.'

PACKAGES = ['FunctionPackage']  # name of the package
print("executing Extension")
print("list of include directories")
include_directories = np.get_include()
print(include_directories)

ext_1 = Extension("rectangleExtension", # name of the module
                  [SRC_DIR + "/src/Rectangle.cpp",
                     SRC_DIR + "/rect.pyx"],
                  libraries=[],
                  include_dirs=[include_directories], # to prevent fatal error: numpy/arrayobject.h: No such file or directory #include "numpy/arrayobject.h"
                  language="c++",  # so that the compiler knows about the language
                  extra_compile_args=["-std=c++11"],
                  extra_link_args=["-std=c++11"],
                  #define_macros = [('NPY_NO_DEPRECATED_API', 'NPY_1_7_API_VERSION')]
                  )


EXTENSIONS = [ext_1]

if __name__ == "__main__":
    print("executing setup")
    setup(install_requires=REQUIRES,
          packages=PACKAGES,
          zip_safe=False,
          name=NAME,
          version=VERSION,
          description=DESCR,
          author=AUTHOR,
          author_email=EMAIL,
          url=URL,
          license=LICENSE,
          cmdclass={"build_ext": build_ext},
          ext_modules=EXTENSIONS,
          include_dirs=[include_directories]
          )
    

