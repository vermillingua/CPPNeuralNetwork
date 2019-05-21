#include <iostream>

#include "matrix/Matrix.hpp"

int main()
{
	Matrix a(3, 4);
	a.fill(2);
	std::cout << a.str();

	Matrix b(3, 4);
	b.fill(1);
	std::cout << b.str();

	a.add(&b);
	std::cout << a.str();

	return -1;
}


