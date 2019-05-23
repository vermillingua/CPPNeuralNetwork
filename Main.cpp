#include <iostream>
#include <random>

#include "matrix/Matrix.hpp"

std::uniform_real_distribution<double> range(-1, 1);
std::default_random_engine engine;

double rand(double a)
{
	return range(engine);
}

double set(double a)
{
	return 2;
}

int main(int argc, char** argv)
{
	std::cout << "Hello World!" << std::endl;
	Matrix a(4, 3);
	//a.map([](double a) {return 1.0;}); // Lambda function doesn't work
	a.map(set);
	std::cout << a.str() << "\n";

	Matrix b(3, 4);
	b.map(rand);
	std::cout << b.str() << "\n";

	Matrix* c = Matrix::dotProd(&a, &b);

	std::cout << c->str() << "\n";

	delete c;

	return -1;
}


