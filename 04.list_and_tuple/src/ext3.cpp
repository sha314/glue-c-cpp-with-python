extern "C"{
#include <Python.h>
}
#include <iostream>
#include <vector>
#include "ext3.h"

// from numpy
// #include <arrayobject.h>
// #include <arrayscalars.h>
// #include <halffloat.h>
// #include <ndarrayobject.h>
// #include <ndarraytypes.h>
// #include <noprefix.h>
// #include <numpyconfig.h>
// #include <ufuncobject.h>
// #include <utils.h>


// use with python3.x
using namespace std;

struct module_state {
    PyObject *error;
};


#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))


/****
Must be called from C++
only to convert to a vector
todo: 
    apply PyLong_AsLong for long
          double for double
          int for int
          ...
****/
template <class T>
std::vector<T> to_vector(PyObject *list){
    cout << "to_vector(PyObject*) : line " << __LINE__ << endl;
    Py_ssize_t i, n;
    T value;
    PyObject *item;
    n = PyList_Size(list);
    cout << "number of elements " << n  << " : line " << __LINE__ << endl;
    vector<T> vec(n);
    if (n < 0){
        cerr << "Not a list : line " << __LINE__ << endl;
        exit(-1);
    }
    for (i = 0; i < n; i++) {
//      cout << "line :" << __LINE__ << endl;       
        item = PyList_GetItem(list, i); /* Can't fail */
        if (!PyLong_Check(item)) continue; /* Skip non-integers */
        value = PyLong_AsLong(item);
//      cout << "line :" << __LINE__ << endl;
        if (value == -1 && PyErr_Occurred()){
            /* Integer too big to fit in a C long, bail out */
            cout << "Integer too big to fit in a C long, bail out. line :" << __LINE__ << endl;
            exit(-1);            
        }
//          cout << "line :" << __LINE__ << endl;
        vec[i] = value;
    }
    return vec;
}


// template <class T>
// PyObject * to_python_list(std::string tp, std::vector<T>& vec){
//     cout << "to_python_list(std::string, PyObject*) : line " << __LINE__ << endl;
//     size_t n = vec.size();
//     Py_ssize_t sz = n;
//     PyObject * list = PyList_New(sz);  // new list of size n
//     sz = PyList_Size(list);
//     cout <<  sz;
//     PyObject *item;
    

//     for(size_t i{}; i < n ; ++i){
//         // item = Py_BuildValue("l", vec[i]); // only for long
//         item = Py_BuildValue(tp.c_str(), vec[i]);
//         if(!PyList_SetItem(list, i, item)){
//             continue;
//         }else{
//             cerr << "cannot set item : line " << __LINE__ << endl;
//             exit(-1);
//         }
//     }

//     return list;
// }



/**
copy imput python list and convert it to c++ vector then sum it and return the result
*/
PyObject *
copy_and_sum(PyObject *self, PyObject *list)
{

    vector<long> vec = to_vector<long>(list);
    long total{};
    cout << "c++ vector" << endl;
    cout << '{';    
    for (size_t i{}; i < vec.size(); i++) {
    	cout << vec[i] << ',';
        total += vec[i];
    }
    cout << '}' << endl;
	vec.clear();
    return Py_BuildValue("l", total);
}

/**
adding two list
**/
// PyObject *
// add_two_array(PyObject *self, PyObject *list1, PyObject *list2)
// {
//     cout << "c++ : parsing first list" << endl;
//     vector<long> vec1 = to_vector<long>(list1);
//     cout << "c++ : parsing 2nd list" << endl;
//     vector<long> vec2 = to_vector<long>(list2);
//     if(vec1.size() != vec2.size()){
//         cout << "size mismatched : line " << __LINE__ << endl;
//         return nullptr;
//     }
//     vector<long> vec3(vec1.size()); 
//     for (size_t i{}; i < vec1.size(); i++) {
//         vec3[i] = vec1[i] + vec2[i];
//     }

//     vec1.clear();
//     vec2.clear();

//     return to_python_list<long>("l", vec3);
// }

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
    cout << "number of elements " << n  << " : line " << __LINE__ << endl;
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




static PyObject *
error_out(PyObject *m) {
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;
}

/***********************************************************
List of method definitions
**/
static PyMethodDef myextension_methods[] = {
    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {"copy_and_sum", (PyCFunction)copy_and_sum, METH_O, "copy_and_sum"},
    {"sum_list", (PyCFunction)sum_list, METH_O, "sum_list"},
    // {"add_two_list", (PyCFunction)add_two_array, METH_VARARGS, "add two list"},
    // {"view_numpy_array", (PyCFunction)view_numpy_array, METH_VARARGS, "numpy array view"},
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

/***************************************************************
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

/******************************************************************
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
