
#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(int layers, int* layer_sizes)
{
	this->layers = layers;
	weights = new Matrix*[layers];
	biases = new Matrix*[layers];

	for (int i = 0; i < layers - 1; i++) //I don't think this will work
	{
		weights[i] = new Matrix(layer_sizes[i], layer_sizes[i - 1]);
		biases[i] = new Matrix(layer_sizes[i], 1);
	}
}

NeuralNetwork::~NeuralNetwork()
{
	for (int i = 0; i < layers; i++) {
		delete weights[i];
		delete biases[i];
	}

	delete [] weights;
	delete[] biases;
}

Matrix* NeuralNetwork::feedForward(Matrix* input)
{
	Matrix* result = input;
	for (int i = 0; i < layers; i++) 
	{
		*result = *weights[i] * *result + *biases[i];
	}
	return result;
}


