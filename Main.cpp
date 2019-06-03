#include <iostream>
#include <random>

#include "neural-network/NeuralNetwork.hpp"
//#include "mnist/mnist.h"

#include "math/Vector.h"

template<typename T>
void printSTDVec(std::vector<T> vec)
{
	for (auto i = vec.begin(); i != vec.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	std::ifstream imageFile("mnist-data/train-images-idx3-ubyte");
	std::ifstream labelFile("mnist-data/train-labels-idx1-ubyte");
	std::vector<Image> images;

	Image::loadFiles(imageFile, labelFile, images);

	//std::vector<int> layers = {784, 32, 32, 10};
	//NeuralNetwork nn(layers);
	NeuralNetwork nn("01.nn");

	int num = 2;
	for (int i = 0; i < num; i++) 
	{
		std::cout << images[i] << std::endl;
		std::cout << nn.classify(images[i]) << std::endl;
	}

	for (int i = 0; i < 1; i++) 
	{
		for (int i = 0; i < 30000; i++) 
		{
			nn.train(images[i]);
		}
		std::cout << "." << std::endl;

		nn.saveTo("01.nn");
	}

	for (int i = 0; i < num; i++) 
	{
		std::cout << "i = " << i << " " <<  nn.classify(images[i]) << std::endl;
	}

	nn.saveTo("01.nn");


	return -1;
}


