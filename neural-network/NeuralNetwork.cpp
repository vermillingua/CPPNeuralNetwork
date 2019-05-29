
#include "NeuralNetwork.hpp"

#include <random>
#include <cmath>
#include <fstream>

NeuralNetwork::NeuralNetwork(std::vector<int> input)
{
	this->layers = input.size() - 1;
	weights = new Matrix[layers];
	biases = new Vector[layers];
	for (int i = 0; i < this->layers; i++) 
	{
		weights[i] = Matrix(input[i + 1], input[i], 0);
		biases[i] = Vector(input[i + 1], 0);
	}
	initialize();

	for (int i = 0; i < this->layers; i++) {
		std::cout << "Layer: " << i << std::endl;
		std::cout << weights[i] << std::endl;
		std::cout << biases[i] << std::endl;
	}
}

NeuralNetwork::NeuralNetwork(std::string path)
{
	std::ifstream file(path);
	if(file.is_open())
	{
		file.read((char*)(&layers), sizeof(unsigned int));
		weights = new Matrix[layers];
		biases = new Vector[layers];
		for (int i = 0; i < layers; i++) 
		{
			file >> weights[i];
			file >> biases[i];
		}
	}
	file.close();
}

NeuralNetwork::~NeuralNetwork()
{
	delete [] weights;
	delete[] biases;
}

std::uniform_real_distribution<double> range(-1, 1);
std::default_random_engine engine;

double rand(double x) // Change later?
{
	return range(engine);
}

void NeuralNetwork::initialize()
{
	for (int i = 0; i < layers; i++) {
		weights[i].map(rand);
		biases[i].map(rand);
	}
}

double sigmoid(double x)
{
	return 1 / (1 + std::exp(-x));
}

double sigmoidPrime(double x)
{
	return std::exp(-x) / ((1 + std::exp(-x)) * (1 + std::exp(-x)));
}

Vector NeuralNetwork::feedForward(const Vector& input) const
{
	Vector result = input;
	for (int i = 0; i < layers; i++) 
		result = (weights[i] * result + biases[i]).map(sigmoid);
	return result;
}

double NeuralNetwork::cost(const Vector& actual, const Vector& desired)
{
	return (actual - desired).map([](double x){return x * x;}).sum();
}

std::vector<double> NeuralNetwork::classify(std::vector<double> input) const
{
	Vector a = input;
	a = feedForward(a);
	return a.toSTDVector();
}

void NeuralNetwork::saveTo(std::string path) const
{
	std::ofstream file(path);
	file.write((char*)(&layers), sizeof(unsigned int));
	for (int i = 0; i < layers; i++) 
	{
		file << weights[i];
		file << biases[i];
	}
	file.close();
}
