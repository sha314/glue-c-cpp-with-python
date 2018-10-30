/* File : example.c */
 
 /*
 So you want to get going in a hurry?
 To illustrate the use of SWIG, suppose you have some C 
 functions you want added to Python. 
 Specifically, let's say you have them in a file 'example.c'
 */
#include <time.h>
#include <iostream>

using namespace std;

double My_variable = 3.0;

void hello_world(){
	cout << "hello world" << endl;
}

size_t fact(size_t n) {
	size_t prod = 1;
	while (n > 1){
		prod *= n;
		--n;
	}
	return n;
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