// converter.h

#ifndef __HEADER_CONVERTER_H__
#define __HEADER_CONVERTER_H__

#include <Python.h>
#include <iostream>
#include <vector>
#include <type_traits>

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
    std::cout << "to_vector(PyObject*) : line " << __LINE__ << std::endl;
    Py_ssize_t i, n;
    T value;
    PyObject *item;
    n = PyList_Size(list);
    std::cout << "number of elements " << n  << " : line " << __LINE__ << std::endl;
    std::vector<T> vec(n);
    if (n < 0){
        std::cerr << "Not a list : line " << __LINE__ << std::endl;
        exit(-1);
    }
    for (i = 0; i < n; i++) {
//      std::cout << "line :" << __LINE__ << std::endl;       
        item = PyList_GetItem(list, i); /* Can't fail */
        if (!PyLong_Check(item)) continue; /* Skip non-integers */
        value = PyLong_AsLong(item);
//      std::cout << "line :" << __LINE__ << std::endl;
        if (value == -1 && PyErr_Occurred()){
            /* Integer too big to fit in a C long, bail out */
            std::cout << "Integer too big to fit in a C long, bail out. line :" << __LINE__ << std::endl;
            exit(-1);            
        }
//          std::cout << "line :" << __LINE__ << std::endl;
        vec[i] = value;
    }
    return vec;
}


// template <class T>
// std::vector<T> to_vector_v2(PyObject *list){
//         // checking type
//     if (std::is_same<T, int>){

//     }else if (std::is_same<T, long>){

//     }else if (std::is_same<T, unsigned int>){

//     }else if (std::is_same<T, unsigned long>){

//     }else if (std::is_same<T, float>){

//     }else if (std::is_same<T, double>){

//     }
//     std::cout << "to_vector(PyObject*) : line " << __LINE__ << std::endl;
//     Py_ssize_t i, n;
//     T value;
//     PyObject *item;
//     n = PyList_Size(list);
//     std::cout << "number of elements " << n  << " : line " << __LINE__ << std::endl;
//     vector<T> vec(n);
//     if (n < 0){
//         std::cerr << "Not a list : line " << __LINE__ << std::endl;
//         exit(-1);
//     }
//     for (i = 0; i < n; i++) {
// //      std::cout << "line :" << __LINE__ << std::endl;       
//         item = PyList_GetItem(list, i); /* Can't fail */
//         if (!PyLong_Check(item)) continue; /* Skip non-integers */
//         value = PyLong_AsLong(item);
// //      std::cout << "line :" << __LINE__ << std::endl;
//         if (value == -1 && PyErr_Occurred()){
//             /* Integer too big to fit in a C long, bail out */
//             std::cout << "Integer too big to fit in a C long, bail out. line :" << __LINE__ << std::endl;
//             exit(-1);            
//         }
// //          std::cout << "line :" << __LINE__ << std::endl;
//         vec[i] = value;
//     }
//     return vec;
// }


template <class T>
PyObject * to_python_list(std::string tp, std::vector<T>& vec){
    std::cout << "to_python_list(std::string, PyObject*) : line " << __LINE__ << std::endl;
    size_t n = vec.size();
    Py_ssize_t sz = n;
    PyObject * list = PyList_New(sz);  // new list of size n
    sz = PyList_Size(list);
    std::cout <<  sz;
    PyObject *item;
    

    for(size_t i{}; i < n ; ++i){
        // item = Py_BuildValue("l", vec[i]); // only for long
        item = Py_BuildValue(tp.c_str(), vec[i]);
        if(!PyList_SetItem(list, i, item)){
            continue;
        }else{
            std::cerr << "cannot set item : line " << __LINE__ << std::endl;
            exit(-1);
        }
    }

    return list;
}

#endif // __HEADER_CONVERTER_H__