
#include "NeuralNetwork.hpp"

#include <random>

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
	//TODO
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

Vector NeuralNetwork::feedForward(const Vector& input) const
{
	Vector result = input;
	for (int i = 0; i < layers; i++) 
		result = weights[i] * result + biases[i];
	return result;
}

double NeuralNetwork::cost(const Vector& actual, const Vector& desired)
{
	Vector cost = actual - desired;
	cost.map([](double x){return x * x;});
	return cost.sum();
}

std::vector<double> NeuralNetwork::classify(std::vector<double> input) const
{
	Vector a = input;
	a = feedForward(a);
	return a.toSTDVector();
}
