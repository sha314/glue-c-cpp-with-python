//converter.cpp

#include "./include/converter.h"
#include "./include/matrix.h"

using namespace std;



vector<vector<long>> get_matrix(PyObject* list){
    //cout << "entered C++" << endl;
    vector<vector<long>> mat;
    long value;
    if(PyList_Check(list)){
        Py_ssize_t i,j, r, c;
        PyObject *item, *next_item;
        r = PyList_Size(list);
        mat.resize(r);
        // cout << "number of elements " << n << endl;
        for (i = 0; i < r; i++) {
    //      cout << "line :" << __LINE__ << endl;       
            item = PyList_GetItem(list, i); /* Can't fail */
            if(PyList_Check(list)){
                c = PyList_Size(item);
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
    //cout << "view matrix in c++" << endl;
    // view(mat);
    // cout << "exiting C++" << endl;
    return mat;
}


PyObject * get_python_matrix(vector<vector<long>>& mat){
    std::cout << "get_python_matrix(vector<vector<long>>) : line " << __LINE__ << std::endl;
    size_t row = mat.size();
    PyObject * list = PyList_New(row);  // new list of size n
    // sz = PyList_Size(list);
    // std::cout <<  sz;
    PyObject *item;
    ;
    
	size_t col;
    for(size_t i{}; i < row ; ++i){
        
    	col = mat[i].size();
    	item = PyList_New(col);
    	for(size_t j{}; j < col; ++j){
            
	        // item = Py_BuildValue("l", vec[i]); // only for long
	        PyObject *tmp = Py_BuildValue("l", mat[i][j]);
            
	        if(!PyList_SetItem(item, j, tmp)){
	            continue;
	        }else{
	            std::cerr << "cannot set item : line " << __LINE__ << std::endl;
	            exit(-1);
	        }
    	}
		if(!PyList_SetItem(list, i, item)){
            continue;
        }else{
            std::cerr << "cannot set item : line " << __LINE__ << std::endl;
            exit(-1);
        }
    }

    return list;
}

