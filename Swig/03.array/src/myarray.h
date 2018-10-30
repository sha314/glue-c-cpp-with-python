
//Word.h


#ifndef __HEADER_MYARRAY_H_
#define __HEADER_MYARRAY_H_

#include <vector>

std::vector<double> ones(size_t sz);
void sum(std::vector<double> v);

/**
view a matrix
**/
void view(std::vector<std::vector<double>> v);

std::vector<std::vector<double>>
matrix_mul(
	std::vector<std::vector<double>> mat1,
	 std::vector<std::vector<double>> mat2);

#endif // WORD_H_ 