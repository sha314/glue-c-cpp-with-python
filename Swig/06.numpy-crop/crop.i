%module crop
%{
#include <errno.h>
#include "crop.h"

#define SWIG_FILE_WITH_INIT
%}

%include "numpy.i"

%init %{
    import_array();
%}

%exception crop
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

// preparing for int values
%apply (int* IN_ARRAY2, int DIM1, int DIM2) {(int *arr_in, int dim1, int dim2)}
%apply (int** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(int **arr_out, int *dim1_out, int *dim2_out)}

// preparing for long values
%apply (long* IN_ARRAY2, int DIM1, int DIM2) {(long *arr_in, int dim1, int dim2)}
%apply (long** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(long **arr_out, int *dim1_out, int *dim2_out)}

%include "crop.h"