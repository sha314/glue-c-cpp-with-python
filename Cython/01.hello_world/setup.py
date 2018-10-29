from setuptools import setup, Extension
from Cython.Distutils import build_ext


NAME = "cython-example"
VERSION = "0.1"
DESCR = "shows how to wrap C/C++ code into python using Cython"
URL = ""
REQUIRES = ['cython']

AUTHOR = "M.S. Rahman"
EMAIL = "shahnoor3pl@gmail.com"

LICENSE = ""

SRC_DIR = "."  # source file directory
out_extension_directory = '.'

PACKAGES = ['HelloPackage']  # name of the package
print("executing Extension")
# print("list of include directories")
# include_directories = np.get_include()
# print(include_directories)

ext_1 = Extension("helloextension", # name of the module
                  [SRC_DIR + "/src/cfunc.cpp",
                     SRC_DIR + "/wrapped.pyx"],
                  libraries=[],
                  include_dirs=[],
                  language="c++",  # so that the compiler knows about the language
                  extra_compile_args=["-std=c++11"],
                  extra_link_args=["-std=c++11"]
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
          ext_modules=EXTENSIONS
          )
