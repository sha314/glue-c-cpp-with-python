//matrix.cpp

#include "./include/matrix.h"
#include <iostream>

using namespace std;

/**
view a matrix
**/
void view(std::vector<std::vector<long>>& v){
	cout << '{';
	for(size_t i{}; i < v.size(); ++i){
		cout << '{';
		for(size_t j{}; j < v[i].size(); ++j){
			cout << v[i][j] << ',';
		}
		cout << '}' << endl;
	}
	cout << '}' << endl;
}


std::vector<std::vector<long>>
matrix_mul(std::vector<std::vector<long>>& mat1, std::vector<std::vector<long>>& mat2){
	size_t row1 = mat1.size();
	size_t row2 = mat2.size();

	size_t col1 = mat1[0].size();
	size_t col2 = mat2[0].size();
	if(col1 != row2){
		cerr << "row2 != col1 : " << __LINE__ << endl;
		return {};
	}

	std::vector<std::vector<long>> mat3(row1);
	for(size_t i{}; i < row1; ++i){
		mat3[i].resize(col2);
		for(size_t j{}; j < col2; ++j){
			for(size_t k{}; k < col1 ; ++k){
				mat3[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
	

	return mat3;
}