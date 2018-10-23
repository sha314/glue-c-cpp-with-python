//view.cpp

#include "./include/view.h"

using namespace std;


void view_python_list_recursive(PyObject* list){
    if(PyList_Check(list)){
        Py_ssize_t i, n;
        PyObject *item;
        n = PyList_Size(list);
        // cout << "number of elements " << n << endl;
        cout << '{';
        if (n < 0)
            return; /* Not a list */
        for (i = 0; i < n; i++) {
    //      cout << "line :" << __LINE__ << endl;       
            item = PyList_GetItem(list, i); /* Can't fail */
            view_python_list_recursive(item);           
        }
        cout << '}' << endl;
    }else{
        // cout << "not a list" << endl;
        if (!PyLong_Check(list)) return; // Skip non-integers 
        long  value = PyLong_AsLong(list);
        //      cout << "line :" << __LINE__ << endl;
        if (value == -1 && PyErr_Occurred()) return;
        /* Integer too big to fit in a C long, bail out */
        cout << value << ',';
        //          cout << "line :" << __LINE__ << endl;
    }
}