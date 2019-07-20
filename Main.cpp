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

void load_files(std::vector<std::vector<double>>& input, std::vector<std::vector<double>>& output,
	std::vector<Image>& images, std::string image_file_path, std::string label_file_path)
{
	std::ifstream image_file(image_file_path);
	std::ifstream label_file(label_file_path);

	Image::loadFiles(image_file, label_file, images);

	input.resize(images.size());
	output.resize(images.size());

	for (int i = 0; i < images.size(); i++) 
	{
		input[i] = images[i].toVector();
		output[i] = std::vector<double>(10, 0.0);
		output[i][images[i].getLabel()] = 1;
	}
}

int main(int argc, char** argv)
{
	std::vector<std::vector<double>> input, output;
	std::vector<Image> images;
	load_files(input, output, images, 
		"mnist-data/train-images-idx3-ubyte", "mnist-data/train-labels-idx1-ubyte");

	std::vector<int> layers = {784, 32, 32, 10};
	//NeuralNetwork nn(layers);
	NeuralNetwork nn("02.nn");

	int num = 2;
	for (int i = 0; i < num; i++) 
	{
		std::cout << images[i] << std::endl;
		printSTDVec(nn.classify(images[i].toVector()));
		printSTDVec(output[i]);
	}

	nn.train(input, output, 20, .001);


	for (int i = 0; i < num; i++) 
	{
		printSTDVec(nn.classify(images[i].toVector()));
	}

	std::cout << images.size() << std::endl;

	nn.saveTo("02.nn");

	return -1;
}


