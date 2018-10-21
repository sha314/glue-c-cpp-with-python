

#include "./include/ext3.h"
#include "./include/converter.h"

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
    Py_ssize_t i, n;
    long  value;
    PyObject *item;
    n = PyList_Size(list);
    cout << "number of elements " << n << endl;
    cout << '{';
    if (n < 0)
        return NULL; /* Not a list */
    for (i = 0; i < n; i++) {
//      cout << "line :" << __LINE__ << endl;       
        item = PyList_GetItem(list, i); /* Can't fail */
        if (!PyLong_Check(item)) continue; // Skip non-integers 
        value = PyLong_AsLong(item);
//      cout << "line :" << __LINE__ << endl;
        if (value == -1 && PyErr_Occurred())
            /* Integer too big to fit in a C long, bail out */
            return NULL;
//          cout << "line :" << __LINE__ << endl;
        cout << value << ',';
    }
    cout << '}' << endl;
    return Py_BuildValue("l", 0);
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
        // cout << "line :" << __LINE__ << endl;       
        item = PyList_GetItem(list, i); /* Can't fail */
        if (!PyLong_Check(item)) continue; /* Skip non-integers */
        value = PyLong_AsLong(item);
        // cout << "line :" << __LINE__ << endl;
        if (value == -1 && PyErr_Occurred())
            /* Integer too big to fit in a C long, bail out */
            return NULL;
        // cout << "line :" << __LINE__ << endl;
        total += value;
    }

    return Py_BuildValue("l", total);
}

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
//      cout << "line :" << __LINE__ << endl;       
        item = PyList_GetItem(list, i); /* Can't fail */
        if (!PyLong_Check(item)) continue; // Skip non-integers 
        value = PyLong_AsLong(item);
//      cout << "line :" << __LINE__ << endl;
        if (value == -1 && PyErr_Occurred())
            /* Integer too big to fit in a C long, bail out */
            return NULL;
//          cout << "line :" << __LINE__ << endl;
        vec[i] = value;
    }

    cout << "c++ vector" << endl;
    cout << '{';    
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << ',';
        total += vec[i];
    }
    cout << '}' << endl;
    vec.clear();
    return Py_BuildValue("l", total);
}

/**
copy imput python list and convert it to c++ vector 
then square each element it and return the squared sum
*/
PyObject *
copy_and_square_sum(PyObject *self, PyObject *list)
{
    auto vec = list_to_vector<long>(list);
    long total{};
    cout << "c++ vector" << endl;
    cout << '{';    
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << ',';
        total += vec[i] * vec[i];
    }
    cout << '}' << endl;
    vec.clear();
    return Py_BuildValue("l", total);
}


static PyObject*
sum_two_array_by_keyword_args(PyObject *self, PyObject *args, PyObject *kwargs){

    static char* keywords[] = {"a", "b", NULL}; // "a", "b" are the keyword of the argument

    PyObject* a;
    PyObject* b;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO", keywords, &a, &b)) {
        return NULL;
    }
    cout << "c++ : parsing first list" << endl;
    vector<long> vec1 = list_to_vector<long>(a);
    cout << "c++ : parsing 2nd list" << endl;
    vector<long> vec2 = list_to_vector<long>(b);
    if(vec1.size() != vec2.size()){
        cout << "size mismatched : line " << __LINE__ << endl;
        return nullptr;
    }
    vector<long> vec3(vec1.size()); 
    for (size_t i{}; i < vec1.size(); i++) {
        vec3[i] = vec1[i] + vec2[i];
    }

    vec1.clear();
    vec2.clear();

    return vector_to_list<long>("l", vec3);
}

static PyObject* tuple_sum(PyObject* self, PyObject *args) {
    PyObject *py_tuple;
    size_t len;
    
    if (!PyArg_ParseTuple(args, "O", &py_tuple)) {
      return NULL;
    }

    auto vec = tuple_to_vector<long>(py_tuple);
    
    long sum{};
    for(size_t i{}; i < vec.size(); ++i){
        sum += vec[i];
    }
    vec.clear();
   //c_array is our array of ints :)
    return Py_BuildValue("l", sum);
}

/**
 recieve a tuple and then return it by squaring each element
**/
static PyObject* round_trip(PyObject* self, PyObject *args) {
    PyObject *py_tuple;
    size_t len;
    
    if (!PyArg_ParseTuple(args, "O", &py_tuple)) {
      return NULL;
    }

    auto vec = tuple_to_vector<long>(py_tuple);
    
    long sum{};
    for(size_t i{}; i < vec.size(); ++i){
        vec[i] = vec[i]*vec[i];
    }
    PyObject * result = vector_to_tuple<long>("l", vec);
   //c_array is our array of ints :)
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
    {"sum_list", (PyCFunction)sum_list, METH_O, "give a list and I will sum it up"},
    {"copy_and_sum", (PyCFunction)copy_and_sum, METH_O, "give a list and i will copy it to a vector and sum it up"},
    {"copy_and_squared_sum", (PyCFunction)copy_and_square_sum, METH_O, "give a list and i will copy it to a vector and return squared sum"},
    {"tuple_sum", (PyCFunction)tuple_sum, METH_VARARGS, "give a tuple and i will copy it to a vector and return sum"},
    {"round_trip", (PyCFunction)round_trip, METH_VARARGS, "give a tuple and i will copy it to a vector, raise it to 2 and return it"},
    {"copy_and_sum_two_list_by_keyword_args", (PyCFunction)sum_two_array_by_keyword_args, METH_VARARGS | METH_KEYWORDS, "give a list and i will copy it to a vector and return squared sum"},
    

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

