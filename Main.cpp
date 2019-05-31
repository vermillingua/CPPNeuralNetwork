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

	std::vector<int> layers = {784, 32, 32, 10};
	NeuralNetwork nn(layers);

	std::cout << nn.classify(images[0]) << std::endl;
	std::cout << nn.classify(images[1]) << std::endl;
	std::cout << nn.classify(images[2]) << std::endl;
	std::cout << nn.classify(images[3]) << std::endl;

	return -1;
}


