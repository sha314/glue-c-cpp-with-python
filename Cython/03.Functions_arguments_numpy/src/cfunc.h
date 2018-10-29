#ifndef _HELLO_WORLD_HEADER_
#define _HELLO_WORLD_HEADER_
#include <stdio.h>
#include <vector>


void view_array(const std::vector<int>& v);
void view_array_2d(const std::vector<std::vector<int>>& v);

std::vector<int>
add(
	const std::vector<int>& v1,
	const std::vector<int>& v2);


std::vector<std::vector<double>>
mat_mul(
	const std::vector<std::vector<double>>& mat1,
	const std::vector<std::vector<double>>& mat2);

#endif  // _HELLO_WORLD_HEADER_ 