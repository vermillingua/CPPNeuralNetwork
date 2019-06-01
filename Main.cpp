#include <iostream>
#include <random>

#include "neural-network/NeuralNetwork.hpp"
//#include "mnist/mnist.h"

#include "math/Vector.h"

void printSTDVec(std::vector<double> vec)
{
	for (auto i = vec.begin(); i != vec.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	std::ifstream imageFile("t10k-images-idx3-ubyte");
	std::ifstream labelFile("t10k-labels-idx1-ubyte");
	std::vector<Image> images;

	Image::loadFiles(imageFile, labelFile, images);

	std::vector<int> layers = {784, 32, 32, 10};
	NeuralNetwork nn(layers);

	for (int i = 0; i < 10; i++) 
	{
		std::cout << nn.classify(images[i]) << std::endl;
		nn.train(images[i]);
		std::cout << nn.classify(images[i]) << std::endl;
	}

	return -1;
}


