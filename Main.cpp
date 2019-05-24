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
	Matrix a(4, 3);

	Matrix b(3, 4);

	std::cout << a << std::endl;
	std::cout << b << std::endl;

	return -1;
}


