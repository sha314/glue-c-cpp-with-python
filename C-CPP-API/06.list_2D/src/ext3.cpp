

#include "./include/ext3.h"
#include "./include/view.h"
#include "./include/converter.h"
#include "./include/matrix.h"

// use with python3.x
using namespace std;

struct module_state {
    PyObject *error;
};


#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))



/**
view the elements of the list
*/
PyObject *
view(PyObject *self, PyObject *list)
{
    view_python_list_recursive(list);
    return Py_BuildValue("l", 0);
}


/**
copy imput python list and convert it to c++ vector 
then square each element it and return the squared sum
*/
PyObject *
view_matrix(PyObject *self, PyObject *list)
{
    cout << "entered C++" << endl;
    vector<vector<long>> mat;
    long value;
    if(PyList_Check(list)){
        Py_ssize_t i,j, r, c;
        PyObject *item, *next_item;
        r = PyList_Size(list);
        mat.resize(r);
        // cout << "number of elements " << n << endl;
        if (r < 0)  return nullptr; /* Not a list */
        for (i = 0; i < r; i++) {
    //      cout << "line :" << __LINE__ << endl;       
            item = PyList_GetItem(list, i); /* Can't fail */
            if(PyList_Check(list)){
                c = PyList_Size(item);
                if (c < 0) return nullptr; /* Not a list */
                mat[i].resize(c);
                for (j = 0; j < c; j++) {
                    next_item = PyList_GetItem(item, j); /* Can't fail */
                    value = PyLong_AsLong(next_item);
                    if (value == -1 && PyErr_Occurred()){
                        /* Integer too big to fit in a C long, bail out */
                        std::cout << "Integer too big to fit in a C long, bail out. line :" << __LINE__ << std::endl;
                        exit(-1);            
                    }
                    mat[i][j] = value;
                }
            
            }
        }         
    }
    cout << "view matrix in c++" << endl;
    view(mat);
    cout << "exiting C++" << endl;
    return Py_BuildValue("l", 0);
}


static PyObject*
mat_mul(PyObject *self, PyObject *args, PyObject *kwargs){

    static char* keywords[] = {"a", "b", NULL}; // "a", "b" are the keyword of the argument

    PyObject* a;
    PyObject* b;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO", keywords, &a, &b)) {
        return NULL;
    }
    cout << "c++ : parsing first list" << endl;
    auto mat1 = get_matrix(a);
    cout << "c++ : parsing 2nd list" << endl;
    auto mat2 = get_matrix(b);
    
    auto mat3 = matrix_mul(mat1, mat2);
    PyObject* result = get_python_matrix(mat3);
    return result;
}


/**
 recieve a list and then just return it
**/
static PyObject* round_trip(PyObject* self, PyObject *args) {
    cout << "c++ : parsing first list" << endl;
    std::vector<std::vector<long>> mat = get_matrix(args);
    cout << "view matrix" << endl;
    view(mat);
    PyObject * result = get_python_matrix(mat);
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
    {"view", (PyCFunction)view, METH_O, "give a list and I will view it's elements"},
    {"view_matrix", (PyCFunction)view_matrix, METH_O, "give a MxN matrix and I will display it"},    
    {"round_trip", (PyCFunction)round_trip, METH_O, "give a matrix. i will view it and return it"},
    {"mat_mul", (PyCFunction)mat_mul, METH_VARARGS | METH_KEYWORDS, "matrix multiplicatoin"},
    

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

// /****
// Numpy array as input
// *****/
// PyObject *
// view_numpy_array(PyObject *self, PyArrayObject *np_array)
// {
//     cout << "trying numpy array : line " << __LINE__ << endl;
//     // int dim = PyArray_NDIM(np_array);
//     // cout << dim << endl;

//     // Py_ssize_t i, n;
//     // long total = 0, value;
//     // PyObject *item;
//     // n = PyList_Size(list);
//     cout << "number of elements " << n  << " : line " << __LINE__ << endl;
//     // if (n < 0)
//     //     return NULL; /* Not a list */
//     // for (i = 0; i < n; i++) {
//     //     cout << "line :" << __LINE__ << endl;       
//     //     item = PyList_GetItem(list, i); /* Can't fail */
//     //     if (!PyLong_Check(item)) continue; /* Skip non-integers */
//     //     value = PyLong_AsLong(item);
//     //     cout << "line :" << __LINE__ << endl;
//     //     if (value == -1 && PyErr_Occurred())
//     //         /* Integer too big to fit in a C long, bail out */
//     //         return NULL;
//     //     cout << "line :" << __LINE__ << endl;
//     //     total += value;
//     // }

//     return Py_BuildValue("l", 0);
// }

