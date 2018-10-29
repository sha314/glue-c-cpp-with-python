#ifndef _HELLO_WORLD_HEADER_
#define _HELLO_WORLD_HEADER_
#include <stdio.h>
#include <vector>

int factorial(int a);
double factorial(double a);  // for overloading test
void view_array(const std::vector<int>& v);
void view_array_2d(const std::vector<std::vector<int>>& v);

#endif  // _HELLO_WORLD_HEADER_ 