#include "./include/ext3.h"
#include <Python.h>

// use with python3.x
using namespace std;

struct module_state {
    PyObject *error;
};


#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))

static PyObject *
hello_world(PyObject *self) {
    cout << "In C++, Hello world" << endl;
    return PyUnicode_FromFormat(""); // returning empty string
}


static PyObject *
say_hello(PyObject *self, PyObject *args) {
    PyObject *result;
    PyObject* name;
    if (!PyArg_ParseTuple(args, "U", &name)){
        return nullptr;
    }

    // Get the actual bytes as a C string
    char* c_str ;
    if(!PyArg_ParseTuple(args, "s", &c_str)){
        return nullptr;
    }

    cout << "In C++, " << c_str << endl;
    result = PyUnicode_FromFormat("Hello, %S!", name);
    return result;
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
    {"hello_world", (PyCFunction)hello_world, METH_NOARGS, "hello world. no argument"},
    {"say_hello", (PyCFunction)say_hello, METH_VARARGS, "hello with one string argument"},
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
