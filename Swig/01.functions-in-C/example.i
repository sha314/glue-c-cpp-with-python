/* example.i */
/*
Now, in order to add these files to your favorite language, you need to write an "interface file" which is the input to SWIG. An interface file for these C functions might look like this
*/
 %module example
 %{
 /* Put header files here or function declarations like below */
 extern double My_variable;
 extern int fact(int n);
 extern int my_mod(int x, int y);
 extern char *get_time();
 %}
 
 extern double My_variable;
 extern int fact(int n);
 extern int my_mod(int x, int y);
 extern char *get_time();