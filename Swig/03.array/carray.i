/* example.i */

%module carray
 %{
 /* Put header files here or function declarations like below */
 #include "src/myarray.h"
 %}

 %include "std_string.i"  // for using std::string in python
 %include "std_vector.i"  // for using std::vector in python
 %include "std_iostream.i" // for using std::iostream in python

 namespace std {
   %template(vectori) vector<int>; // for 1D array
   %template(vectord) vector<double>; // for 1D array
   %template(vectordd) vector<vector<double>>; // for 2D array
};

 %include "src/myarray.h" 

 //extern void sum(std::vector<double> v);
