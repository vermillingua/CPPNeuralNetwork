#include <iostream>
#include <random>

#include "math/Matrix.h"
#include "math/Vector.h"
#include "neural-network/NeuralNetwork.hpp"
#include "mnist/mnist.h"

void printSTDVec(std::vector<double> vec)
{
	for (auto i = vec.begin(); i != vec.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	std::ifstream file("t10k-images-idx3-ubyte");
	std::vector<Image> images;

	Image::loadFile(file, images);

	std::cout << images.size() << std::endl;


	for (int i = 0; i < 10; i++) 
	{
		std::cout << images[i] << std::endl;
	}


	return -1;
}


