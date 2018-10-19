extern "C"{
#include <Python.h>
}
#include <iostream>
#include <vector>
#include "ext3.h"

// use with python3.x
using namespace std;

struct module_state {
    PyObject *error;
};


#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))


/**
copy imput python list and convert it to c++ vector then sum it and return the result
*/
PyObject *
copy_and_sum(PyObject *self, PyObject *list)
{
	Py_ssize_t i, n;
    long total = 0, value;
    PyObject *item;
    n = PyList_Size(list);
    cout << "number of elements " << n << endl;
    vector<long> vec(n);
    if (n < 0)
        return NULL; /* Not a list */
    for (i = 0; i < n; i++) {
//    	cout << "line :" << __LINE__ << endl;    	
        item = PyList_GetItem(list, i); /* Can't fail */
        if (!PyLong_Check(item)) continue; /* Skip non-integers */
    	value = PyLong_AsLong(item);
//    	cout << "line :" << __LINE__ << endl;
        if (value == -1 && PyErr_Occurred())
            /* Integer too big to fit in a C long, bail out */
            return NULL;
//       	cout << "line :" << __LINE__ << endl;
       	vec[i] = value;
    }
    cout << "c++ vector" << endl;
    cout << '{';    
    for (i = 0; i < n; i++) {
    	cout << vec[i] << ',';
        total += vec[i];
    }
    cout << '}' << endl;
	vec.clear();
    return Py_BuildValue("l", total);
}

/***
 take a python list as imput and sum all the values and return the result
***/
PyObject *
sum_list(PyObject *self, PyObject *list)
{
    Py_ssize_t i, n;
    long total = 0, value;
    PyObject *item;
    n = PyList_Size(list);
    cout << "number of elements " << n << endl;
    if (n < 0)
        return NULL; /* Not a list */
    for (i = 0; i < n; i++) {
    	cout << "line :" << __LINE__ << endl;    	
        item = PyList_GetItem(list, i); /* Can't fail */
        if (!PyLong_Check(item)) continue; /* Skip non-integers */
    	value = PyLong_AsLong(item);
    	cout << "line :" << __LINE__ << endl;
        if (value == -1 && PyErr_Occurred())
            /* Integer too big to fit in a C long, bail out */
            return NULL;
       	cout << "line :" << __LINE__ << endl;
        total += value;
    }

    return Py_BuildValue("l", total);
}


static PyObject *
error_out(PyObject *m) {
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;
}

/**
List of method definitions
**/
static PyMethodDef myextension_methods[] = {
    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {"copy_and_sum", (PyCFunction)copy_and_sum, METH_O, "copy_and_sum"},
    {"sum_list", (PyCFunction)sum_list, METH_O, "sum_list"},

    {NULL, NULL}
};


static int myextension_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int myextension_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

/**
module definition
**/
static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "myextension",
        NULL,
        sizeof(struct module_state),
        myextension_methods,
        NULL,
        myextension_traverse,
        myextension_clear,
        NULL
};

#define INITERROR return NULL

/**
 module initialization
**/
PyMODINIT_FUNC
PyInit_myextension(void)
{

    PyObject *module = PyModule_Create(&moduledef);


    if (module == NULL)
        INITERROR;
    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException("myextension.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

    return module;

}
