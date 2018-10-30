/* example.i */
/*
Now, in order to add these files to your favorite language, you need to write an "interface file" which is the input to SWIG. An interface file for these C functions might look like this
*/
 %module cppfunc
 %{
 /* Put header files here or function declarations like below */
 extern double My_variable;
 extern void hello_world();
 extern size_t fact(size_t n);
 extern int my_mod(int x, int y);
 extern char *get_time();
 %}
 
 extern double My_variable;
 extern void hello_world();
 extern size_t fact(size_t n);
 extern int my_mod(int x, int y);
 extern char *get_time();