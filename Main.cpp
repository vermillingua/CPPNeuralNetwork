#include <iostream>

#include "matrix/Matrix.hpp"

int main()
{
	Matrix a(4, 3);
	a.fill(2);
	std::cout << a.str();

	Matrix b(3, 4);
	b.fill(1);
	std::cout << b.str();

	Matrix* c = Matrix::dotProd(&a, &b);

	std::cout << c->str();

	delete c;

	return -1;
}


