#include <Python.h>
#include <iostream>

// use with python3.x
using namespace std;

struct module_state {
    PyObject *error;
};


#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))


static PyObject *
say_hello(PyObject *self, PyObject *args) {
    PyObject *name, *result;

    if (!PyArg_ParseTuple(args, "U:say_hello", &name))
        return NULL;
    cout << "In C++ " << endl;
    result = PyUnicode_FromFormat("Hello, %S!", name);
    return result;
}


static PyObject *
factorial_long(PyObject *self, PyObject *args) {
    PyObject *result;
    cout << "In C++ " << endl;
    long n;
    if (!PyArg_ParseTuple(args, "l", &n))
        return NULL;

    long prod = 1;
    while (n > 1){
        prod *= n;
        --n;
    }
    result = Py_BuildValue("l", prod);
    return result;
}


static PyObject *
factorial_double(PyObject *self, PyObject *args) {
        PyObject *result;
    cout << "In C++ " << endl;
    double n;
    if (!PyArg_ParseTuple(args, "d", &n))
        return NULL;

    double prod = 1;
    while (n > 1){
        prod *= n;
        --n;
    }
    result = Py_BuildValue("d", prod);
    return result;
}


static PyObject *
multiply_two_number(PyObject *self, PyObject *args) {
        PyObject *result;
    cout << "In C++ " << endl;
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b))
        return NULL;

    result = Py_BuildValue("d", a*b);
    return result;
}


static PyObject *
error_out(PyObject *m) {
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;
}

/********************************************************************
List of method definitions
**/
static PyMethodDef myextension_methods[] = {
    // format: python function name, c/c++ function name, argument type, description
    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {"say_hello", (PyCFunction)say_hello, METH_VARARGS, "hello description"},
    {"factorial_long", (PyCFunction)factorial_long, METH_VARARGS, "factorial with long value"},
    {"factorial_double", (PyCFunction)factorial_double, METH_VARARGS, "factorial with double value"},
    {"multiply_two_number_py", (PyCFunction)multiply_two_number, METH_VARARGS, "multiply_two_number double value"},
    {NULL, NULL, 0, NULL}
};


static int myextension_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int myextension_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

/**************************************************************
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

/****************************************************************
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

