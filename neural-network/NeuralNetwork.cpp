
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

void NeuralNetwork::feedForward(Vector activations[], Vector weighted_inputs[]) const
{
	for (int i = 0; i < layers; i++) 
	{
		weighted_inputs[i] = weights[i] * activations[i] + biases[i];
		activations[i + 1] = weighted_inputs[i];
		activations[i + 1].map(sigmoid);
	}
}

void NeuralNetwork::generateErrors(const Vector weighted_inputs[], const Vector activations[], 
	const Vector& target, Vector* errors) const
{
	Vector t = weighted_inputs[layers - 1];
	errors[layers - 1] = (activations[layers] - target) * 
		t.map(sigmoidPrime);

	for (int i = layers - 2; i > -1; i--) 
	{
		Vector temp = weighted_inputs[i];

		errors[i] = (weights[i + 1].transpose() * errors[i + 1]) * 
			temp.map(sigmoidPrime);
	}
}

void NeuralNetwork::backPropagation(const Vector& input, const Vector& target)
{
	Vector weighted_inputs[layers]; // z
	for (int i = 0; i < layers; i++) 
		weighted_inputs[i] = Vector(1, 0);

	Vector activations[layers + 1];
	for (int i = 0; i < layers + 1; i++) 
		activations[i] = Vector(1, 0);
	activations[0] = input;

	feedForward(activations, weighted_inputs);

	Vector errors[layers]; // delta
	for (int i = 0; i < layers; i++) 
		errors[i] = Vector(1, 0);

	generateErrors(weighted_inputs, activations, target, errors);



	for (int i = 0; i < layers; i++) 
	{
		biases[i] -= errors[i] * learningRate;
		weights[i] = weights[i] - (activations[i] * errors[i] * learningRate);
	}

	
}

std::vector<double> NeuralNetwork::classify(std::vector<double> input) const
{
	Vector a = input;
	a = feedForward(a);
	return a.toSTDVector();
}

Vector NeuralNetwork::classify(const Image& image)
{
	Vector a(image.toVector());
	return feedForward(a);
}

void NeuralNetwork::train(const Image& image)
{
	Vector input(image.toVector());
	std::vector<double> a(10, 0);
	a[image.getLabel()] = 1;
	Vector output = a;
	std::cout << image << std::endl;
	std::cout << output << std::endl;
	backPropagation(input, output);
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
