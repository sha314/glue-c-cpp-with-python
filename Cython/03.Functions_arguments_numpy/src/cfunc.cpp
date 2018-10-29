
#include "cfunc.h"
#include<iostream>
#include <stdio.h>

using namespace std;


// on test
// #ifndef NPY_NO_DEPRECATED_API
// #define NPY_NO_DEPRECATED_API 0
// #endif

// #if NPY_NO_DEPRECATED_API < NPY_API_VERSION
// #warning "..."
// #endif

// #if NPY_NO_DEPRECATED_API < NPY_1_8_API_VERSION
// ///* APIs that were deprecated in numpy 1.8 but that have not yet been removed */
// #endif

// #if NPY_NO_DEPRECATED_API < NPY_1_7_API_VERSION
// ///* APIs that were deprecated in numpy 1.7 but that have not yet been removed */
// #endif

// on test // end

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

/**
 To add two array or list
**/
std::vector<int>
add(
	const std::vector<int>& v1,
	const std::vector<int>& v2
){
	if (v1.size() != v2.size()){
		cout << "Size mismatched !" << endl;
		return std::vector<int>();
	}
	std::vector<int> v3(v1.size());
	for(size_t i{}; i < v1.size(); ++i){
		v3[i] = v1[i] + v2[i];
	}
	return v3;
}

/*
Matrix multiplication
*/

std::vector<std::vector<double>>
mat_mul(
	const std::vector<std::vector<double>>& mat1,
	const std::vector<std::vector<double>>& mat2){
	size_t row1 = mat1.size();
	size_t col1 = mat1[0].size();

	size_t row2 = mat2.size();
	size_t col2 = mat2[0].size();

	if(col1 != row2){
		cout << "dimension mismatched" << endl;
		return mat1;
	}
	std::vector<std::vector<double>> mat(row1);
	for(size_t i{}; i <row1; ++i){
		mat[i].resize(col2);
		for(size_t j{}; j < col2; ++j){
			for(size_t k{}; k < col1; ++k){
				mat[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
	return mat;
}