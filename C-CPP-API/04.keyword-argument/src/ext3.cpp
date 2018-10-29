#include "./include/ext3.h"
// use with python3.x
using namespace std;

struct module_state {
    PyObject *error;
};


#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))

/*
 METH_KEYWORDS for Key word arguments
 */
/*
Only long argument is acceptable
*/
static PyObject *
one_keyword_argument(PyObject *self,
                                 PyObject *args,
                                 PyObject *kwargs){


    /* the names of the arguments as a static array */
    static char* keywords[] = {"n", NULL}; // n is the keyword

    PyObject* n;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", keywords, &n)) {
        /* the arguments passed don't correspond to the signature
           described */
        return nullptr;
    }

    cout << "n: " << PyLong_AsLong(n) << endl; // showing the keyword argument value

    return PyUnicode_FromFormat(""); // return empty string
}


static PyObject*
mandatory_keyword_argument_add(PyObject *self,
                                 PyObject *args,
                                 PyObject *kwargs){

    static char* keywords[] = {"a", "b", NULL}; // "a", "b" are the keyword of the argument

    int a;
    int b;

    if (!PyArg_ParseTupleAndKeywords(args,
                                     kwargs,
                                     "ii",
                                     keywords,
                                     &a,
                                     &b)) {
        return NULL;
    }
    return PyLong_FromLong(a + b);
}


static PyObject*
optional_keyword_argument_add(PyObject *self,
                                 PyObject *args,
                                 PyObject *kwargs){

    static char* keywords[] = {"a", "b", NULL}; // "a", "b" are the keyword of the argument

    int a;
    int b=0;

    if (!PyArg_ParseTupleAndKeywords(args,
                                     kwargs,
                                     "i|i",
                                     keywords,
                                     &a,
                                     &b)) {
        return NULL;
    }

    if(b==0){
        cout << "second argument is not provided"
             << "and default value is used" << endl;
    }
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;

    return PyLong_FromLong(a + b);
}


static PyObject*
optional_keyword_argument_py_object(PyObject *self,
                                 PyObject *args,
                                 PyObject *kwargs){

    static char* keywords[] = {"a", "b", NULL}; // "a", "b" are the keyword of the argument

    PyObject* a;
    PyObject* b=nullptr;
    long c_a{}, c_b{};
    if (!PyArg_ParseTupleAndKeywords(args,
                                     kwargs,
                                     "O|O",
                                     keywords,
                                     &a,
                                     &b)) {
        return NULL;
    }
    c_a = PyLong_AsLong(a);
    
    if(b==nullptr){
        cout << "second argument is not provided"
             << "and default value is used" << endl;
        c_b = 0;
    }else{
        c_b = PyLong_AsLong(b);
    }
    cout << "a=" << c_a << endl;
    cout << "b=" << c_b << endl;

    return PyLong_FromLong(c_a + c_b);
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
    {"one_keyword_argument", (PyCFunction)one_keyword_argument, METH_VARARGS | METH_KEYWORDS, "one (long) keyword argument"},
    {"mandatory_keyword_argument_add", (PyCFunction)mandatory_keyword_argument_add, METH_VARARGS | METH_KEYWORDS, "two mandatory keyword argument"},
    {"optional_keyword_argument_add", (PyCFunction)optional_keyword_argument_add, METH_VARARGS | METH_KEYWORDS, "two keyword argument. one optional"},
    {"optional_keyword_argument_py_object", (PyCFunction)optional_keyword_argument_py_object, METH_VARARGS | METH_KEYWORDS, "two keyword argument. one optional. both are general type PyObject*"},
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

