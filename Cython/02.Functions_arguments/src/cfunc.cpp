
#include "cfunc.h"
#include<iostream>
#include <stdio.h>

using namespace std;


int factorial(int a){
	cout << "int factorial(int) : line " <<__LINE__ << endl;
	int b=1;
	while (a > 1){
		b *= a;
		a--;
	}
	return b;
}

double factorial(double a){
	cout << "double factorial(double) : line " <<__LINE__ << endl;
	double b=1;
	while (a > 1){
		b *= a;
		a--;
	}
	return b;
}

void view_array(const std::vector<int>& v){
	cout << '{';
	for(size_t i{}; i < v.size(); ++i){
		cout << v[i] << ',';
	}
	cout << '}' << endl;
}


void view_array_2d(const std::vector<std::vector<int>>& v){
	cout << '{';
	for(size_t i{}; i < v.size(); ++i){
		view_array(v[i]);
	}
	cout << '}' << endl;
}