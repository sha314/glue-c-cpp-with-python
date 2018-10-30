/* File : example.c */
 
 /*
 So you want to get going in a hurry?
 To illustrate the use of SWIG, suppose you have some C 
 functions you want added to Python. 
 Specifically, let's say you have them in a file 'example.c'
 */
#include <time.h>
double My_variable = 3.0;

int fact(int n) {
	if (n <= 1) return 1;
	else return n*fact(n-1);
}

int my_mod(int x, int y) {
	return (x%y);
}
	
char *get_time()
{
	time_t ltime;
	time(&ltime);
	return ctime(&ltime);
}