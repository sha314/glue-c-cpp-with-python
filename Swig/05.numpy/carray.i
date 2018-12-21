%module carray

%{
    #define SWIG_FILE_WITH_INIT
    #include "src/myarray.h"
%}

%include "numpy.i"

%init %{
    import_array();
%}

 %include "std_string.i"  // for using std::string in python
 %include "std_vector.i"  // for using std::vector in python
 %include "std_iostream.i" // for using std::iostream in python
 
// argout array
%apply (int* ARGOUT_ARRAY1, int DIM1) {(int* rangevec, int n)}

// inplace array
%apply (double* INPLACE_ARRAY1, int DIM1) {(double* invec, int n)}


%apply (int DIM1, double* IN_ARRAY1) {(int len1, double* vec1), (int len2, double* vec2)}



// dot function
%rename (dot) my_dot;

%inline %{
    double my_dot(int len1, double* vec1, int len2, double* vec2) {
    if (len1 != len2) {
        PyErr_Format(PyExc_ValueError, "Arrays of lengths (%d,%d) given", len1, len2);
        return 0.0;
    }
    return dot(len1, vec1, vec2);
}
%}

 namespace std {
   %template(vectori) vector<int>; // for 1D array
   %template(vectord) vector<double>; // for 1D array
   %template(vectordd) vector<vector<double>>; // for 2D array
};


%apply (int DIM1, double* IN_ARRAY1) {(int len_, double* vec_)}
%rename (foo) my_foo;
%inline %{
int my_foo(int len_, double* vec_) {
    std::vector<double> v;
    v.insert(v.end(), vec_, vec_ + len_);
    return foo(v);
}
%}


%apply (size_t DIM1, size_t DIM2, double* IN_ARRAY2) {(size_t len1_, size_t len2_, double* vec_)}

%rename (bar) my_bar;
%inline %{
int my_bar(size_t len1_, size_t len2_, double* vec_) {
    std::vector< std::vector<double> > v (len1_);
    for (size_t i = 0; i < len1_; ++i) {
        v[i].insert(v[i].end(), vec_ + i*len2_, vec_ + (i+1)*len2_);
    }
    return bar(v);
}
%}

%include "src/myarray.h"

