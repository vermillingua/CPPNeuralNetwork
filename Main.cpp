#include <iostream>
#include <random>

#include "math/Matrix.h"
#include "math/Vector.h"
#include "neural-network/NeuralNetwork.hpp"

void printSTDVec(std::vector<double> vec)
{
	for (auto i = vec.begin(); i != vec.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	std::vector<int> layers = {10, 5, 8, 2};
	NeuralNetwork nn(layers);
	nn.saveTo("one.nn");
	std::vector<double> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::vector<double> output = nn.classify(input);

	printSTDVec(input);
	printSTDVec(output);
	return -1;
}


