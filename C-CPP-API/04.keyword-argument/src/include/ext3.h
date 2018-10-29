
#ifndef __HEADER_EXT3_H__
#define __HEADER_EXT3_H__

#include <Python.h>
#include <iostream>

/*
 METH_KEYWORDS for Key word arguments

 */
static PyObject *
one_keyword_argument(
	PyObject *self, PyObject *args, PyObject *kwargs);


static PyObject*
mandatory_keyword_argument_add(PyObject *self,
                                 PyObject *args,
                                 PyObject *kwargs);

static PyObject*
optional_keyword_argument_add(PyObject *self,
                                 PyObject *args,
                                 PyObject *kwargs);


static PyObject * error_out(PyObject *m);

#endif // __HEADER_EXT3_H__
