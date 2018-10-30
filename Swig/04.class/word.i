/* example.i */

%module word
 %{
 /* Put header files here or function declarations like below */
 #include "src/word.h"
 %}

 %include "std_string.i"  // for using std::string in python
 %include "src/word.h" 