# cython-example
Wrapping C/C++ code with cython

This is a tutorial based repository.

```
Operating system:
Originally written in linux. Therefore all linux based OS should
be able to compile and run the program

```

```
Required softwares:
	python 3
	cython
	gcc
	g++
	numpy
```

```
Files used for

.pyx -> Cython source
.pxd -> Cython header
.cpp -> C++ source file
.h   -> C/C++ header file
.c   -> C source file
```

```
How to build and run:
each folder contains "run.sh" file
run the file from terminal and that should do all the work

```

```
Example list

01.hello_world
	The famous hello world example. In addition there is a function that takes one int argument and return an int value.

02.	
```

```
Warning
	warning: #warning "Using deprecated NumPy API, disable it by " "#defining NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION" [-Wcpp]
 	#warning "Using deprecated NumPy API, disable it by "
Solution
	do not import the following in the .pxy file
	cimport numpy

```