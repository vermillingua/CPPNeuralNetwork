
#include "NeuralNetwork.hpp"

#include <random>
#include <cmath>
#include <fstream>
#include <algorithm>

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
	delete [] biases;
}

std::uniform_real_distribution<double> range(-1, 1);
std::default_random_engine engine;

double rand(double x)
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
	return sigmoid(x) * (1 - sigmoid(x));
}

Vector NeuralNetwork::feedForward(const Vector& input) const
{
	Vector result = input;
	for (int i = 0; i < layers; i++) 
		result = (weights[i] * result + biases[i]).map(sigmoid);
	return result;
}

void NeuralNetwork::feedForward(Vector weighted_inputs[], Vector activations[]) const
{
	for (int i = 0; i < layers; i++) 
	{
		weighted_inputs[i] = weights[i] * activations[i] + biases[i];
		activations[i + 1] = weighted_inputs[i];
		activations[i + 1].map(sigmoid);
	}
}

void NeuralNetwork::generateErrors(const Vector weighted_inputs[], const Vector activations[], 
	const Vector& target, Vector errors[]) const
{
	Vector t = weighted_inputs[layers - 1];
	errors[layers - 1] = Vector::hamming_product(activations[layers] - target, t.map(sigmoidPrime));

	for (int i = layers - 2; i > -1; i--) 
	{
		Vector temp = weighted_inputs[i];
		errors[i] = Vector::hamming_product(weights[i + 1].transpose() * errors[i + 1], temp.map(sigmoidPrime));
	}
}

void NeuralNetwork::updateWeightsAndBiases(const Vector errors[], const Vector activations[], 
	double learningRate)
{
	for (int i = 0; i < layers; i++) 
	{
		biases[i] -= errors[i] * learningRate;

		Matrix a = outer_prod(errors[i], activations[i]);
		weights[i] = weights[i] - (a * learningRate);
	}
}

std::vector<double> NeuralNetwork::classify(std::vector<double> input) const
{
	return feedForward(Vector(input)).to_std_vector();
}

void c_shuffle(int* list, int size)
{
	for (int i = size - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		int t = list[i];
		list[i] = list[j];
		list[j] = t;
	}
}

void NeuralNetwork::train(std::vector<std::vector<double>> input, 
	std::vector<std::vector<double>> output, int epochs, double learningRate)
{
	std::vector<Vector> v_Input(input.size());
	for (int i = 0; i < v_Input.size(); i++) 
		v_Input[i] = Vector(input[i]);
	
	std::vector<Vector> v_Output(output.size());
	for (int i = 0; i < v_Output.size(); i++) 
		v_Output[i] = Vector(output[i]);
	
	Vector target;

	Vector weighted_inputs[layers]; // z
	Vector activations[layers + 1]; // a
	Vector errors[layers]; // delta

	int list[input.size()];
	for (int i = 0; i < input.size(); i++) 
		list[i] = i;
	
	for (int i = 0; i < epochs; i++) 
	{
		std::cout << "Starting epoch " << (i + 1) << " (of " << epochs << ")..." << std::endl;
		c_shuffle(list, input.size());
		for (int j = 0; j < input.size(); j++) 
		{
			int index = list[j];
			activations[0] = v_Input[index];
			target = v_Output[index];
			
			feedForward(weighted_inputs, activations);
			generateErrors(weighted_inputs, activations, target, errors);
			updateWeightsAndBiases(errors, activations, learningRate);
		}
	}
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
