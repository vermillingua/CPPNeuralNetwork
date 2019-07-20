
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
	delete[] biases;
}

std::uniform_real_distribution<double> range(-1, 1);
std::default_random_engine engine;

double rand(double x) // Change later?
{
	//return 0;
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
	errors[layers - 1] = (activations[layers] - target) * t.map(sigmoidPrime);

	for (int i = layers - 2; i > -1; i--) 
	{
		Vector temp = weighted_inputs[i];
		errors[i] = (weights[i + 1].transpose() * errors[i + 1]) * temp.map(sigmoidPrime);
	}
}

void NeuralNetwork::updateWeightsAndBiases(const Vector errors[], const Vector activations[], 
	double learningRate)
{
	for (int i = 0; i < layers; i++) 
	{
		biases[i] -= errors[i] * learningRate;
		//weights[i] = weights[i] - (activations[i + 1] * errors[i] * learningRate);
		//std::cout << "weights " << i << std::endl;
		//std::cout << weights[i].get_dimentions() << std::endl;
		//std::cout << "activations " << i << std::endl;
		//std::cout << activations[i].get_dimentions() << std::endl;
		//std::cout << "Errors " << i << std::endl;
		//std::cout << errors[i].get_dimentions() << std::endl;

		Matrix a = mult(errors[i], activations[i]);
		//std::cout << "activations * errors" << std::endl;
		//std::cout << a.get_dimentions() << std::endl;
		//std::cout << (a * learningRate).get_dimentions() << std::endl;
		//std::cout << (weights[i] - (a * learningRate)).get_dimentions() << std::endl;

		weights[i] = weights[i] - (a * learningRate);
		//std::cout << "Success@" << std::endl;
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
		weights[i] = weights[i] - (activations[i + 1] * errors[i] * learningRate);
	}
}

std::vector<double> NeuralNetwork::classify(std::vector<double> input) const
{
	return feedForward(Vector(input)).toSTDVector();
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
	
	for (int i = 0; i < epochs; i++) 
	{

		auto rng = std::default_random_engine {};
		std::shuffle(std::begin(input), std::end(input), rng);
		for (int j = 0; j < input.size(); j++) 
		{
			activations[0] = v_Input[j];
			target = v_Output[j];
			
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
