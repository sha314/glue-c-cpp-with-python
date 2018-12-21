%module convolution
%{
#include <errno.h>
#include "convolution.h"

#define SWIG_FILE_WITH_INIT
%}

%include "numpy.i"

%init %{
    import_array();
%}

/*
%exception convolution
{
    errno = 0;
    $action

    if (errno != 0)
    {
        switch(errno)
        {
            case EPERM:
                PyErr_Format(PyExc_IndexError, "Index error");
                break;
            case ENOMEM:
                PyErr_Format(PyExc_MemoryError, "Not enough memory");
                break;
            default:
                PyErr_Format(PyExc_Exception, "Unknown exception");
        }
        SWIG_fail;
    }
}
*/

 %include "std_string.i"  // for using std::string in python
 %include "std_vector.i"  // for using std::vector in python
 %include "std_iostream.i" // for using std::iostream in python

 namespace std {
   %template(vectori) vector<int>; // for 1D array
   %template(vectord) vector<double>; // for 1D array
   %template(vectordd) vector<vector<double>>; // for 2D array
};


// prepare for 1d array
%apply (double* IN_ARRAY1, int DIM1) {(double *data, int columns)}
%apply (double** ARGOUTVIEWM_ARRAY1, int* DIM1) {(double **data_out, int *dim_out)}



// preparing for 2d array
%apply (double* IN_ARRAY2, int DIM1, int DIM2) {(double *data_in, int n_rows, int n_columns)}
%apply (double** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(double **data_out, int *dim1_out, int *dim2_out)}


%include "convolution.h"