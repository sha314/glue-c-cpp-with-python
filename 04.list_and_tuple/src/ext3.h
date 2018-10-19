#include <iostream>

size_t fact(size_t i){
	size_t prod=1;
	while(i > 1){
		prod *= i--;
	}
	return prod;
}
