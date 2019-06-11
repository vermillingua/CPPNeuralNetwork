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

	std::vector<std::vector<double>> input(images.size());
	std::vector<std::vector<double>> output(images.size());

	for (int i = 0; i < images.size(); i++) 
		input[i] = images[i].toVector();
	
	for (int i = 0; i < images.size(); i++) 
	{
		output[i] = std::vector(10, 0.0);
		output[i][images[i].getLabel()] = 1;
	}

	for (int i = 0; i < 10; i++) 
	{
		std::cout << images[i] << std::endl;
		std::cout << images[i].getLabel() << std::endl;
		printSTDVec(output[i]);
	}

	std::vector<int> layers = {784, 32, 32, 10};
	NeuralNetwork nn(layers);
	//NeuralNetwork nn("02.nn");

	int num = 2;
	for (int i = 0; i < num; i++) 
	{
		std::cout << images[i] << std::endl;
		printSTDVec(nn.classify(images[i].toVector()));
	}

	nn.train(input, output, 1, .1);


	for (int i = 0; i < num; i++) 
	{
		printSTDVec(nn.classify(images[i].toVector()));
	}

	std::cout << images.size() << std::endl;

	nn.saveTo("02.nn");


	return -1;
}


