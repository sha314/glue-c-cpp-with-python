#include <stdio.h>
#include "cfunc.h"
#include<iostream>

using namespace std;

void hello()
{
    puts("hello world!");
}

int factorial(int a){
	int b=1;
	while (a > 1){
		b *= a;
		a--;
	}
	return b;
}

// void view_array(const std::vector<int>& v){
// 	cout << '{';
// 	for(size_t i{}; i < v.size(); ++i){
// 		cout << i << ',';
// 	}
// 	cout << '}' << endl;;
// }