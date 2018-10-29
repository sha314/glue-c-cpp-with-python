#ifndef __HEADER_EXT3_H__
#define __HEADER_EXT3_H__


#include <Python.h>
#include <iostream>


// /****
// Numpy array as input
// *****/
// PyObject * view_numpy_array(PyObject *self, PyArrayObject *np_array);


static PyObject * error_out(PyObject *m);

static PyObject* view(PyObject *self, PyObject *list);
static PyObject* view_matrix(PyObject *self, PyObject *args);
static PyObject* round_trip(PyObject *self, PyObject *list);
static PyObject* mat_mul(
	PyObject *self, PyObject *args, PyObject *kwargs);


#endif // __HEADER_EXT3_H__