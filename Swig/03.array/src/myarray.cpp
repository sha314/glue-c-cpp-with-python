/*
  Word.cpp
 
   Created on: 2015-10-25
       Author: gberseth
 */
#include "myarray.h"
#include <iostream>

using namespace std;

std::vector<double> ones(size_t sz){
	std::vector<double> v(sz);
	for(size_t i{}; i < sz; ++i){
		v[i] = 1.0;
	}
	return v;
}

void sum(vector<double> v){
	double sum{};
	for(size_t i{}; i < v.size(); ++i){
		sum += v[i];
	}
	cout << "sum = " << sum << endl;
}

/**
view a matrix
**/
void view(std::vector<std::vector<double>> v){
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


std::vector<std::vector<double>>
matrix_mul(
	std::vector<std::vector<double>> mat1,
	std::vector<std::vector<double>> mat2
	)
{
	size_t row1 = mat1.size();
	size_t row2 = mat2.size();

	size_t col1 = mat1[0].size();
	size_t col2 = mat2[0].size();
	if(col1 != row2){
		cerr << "row2 != col1 : " << __LINE__ << endl;
		return {};
	}

	std::vector<std::vector<double>> mat3(row1);
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
