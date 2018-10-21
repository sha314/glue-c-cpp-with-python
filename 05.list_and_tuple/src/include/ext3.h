#ifndef __HEADER_EXT3_H__
#define __HEADER_EXT3_H__


#include <Python.h>
#include <iostream>


// /****
// Numpy array as input
// *****/
// PyObject * view_numpy_array(PyObject *self, PyArrayObject *np_array);


static PyObject * error_out(PyObject *m);

static PyObject * view(PyObject *self, PyObject *list);
static PyObject * sum_list(PyObject *self, PyObject *list);
static PyObject * copy_and_sum(PyObject *self, PyObject *list);
static PyObject * copy_and_square_sum(PyObject *self, PyObject *list);

static PyObject* sum_two_array_by_keyword_args(
	PyObject *self, PyObject *args, PyObject *kwargs);

#endif // __HEADER_EXT3_H__