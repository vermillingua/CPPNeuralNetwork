#include <iostream>
#include <random>

#include "math/Matrix.h"
#include "math/Vector.h"

std::uniform_real_distribution<double> range(-1, 1);
std::default_random_engine engine;

double rand(double a)
{
	return range(engine);
}

int main(int argc, char** argv)
{
	Matrix a = {{1, 2, 3},
				{2, 3, 4},
				{3, 4, 5},
				{4, 5, 6}};

	Matrix b(3, 2);
	b.map(rand);

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << (a * b) << std::endl;

	return -1;
}


