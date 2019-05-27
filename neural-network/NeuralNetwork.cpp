
#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(std::vector<int> layers)
{
	//TODO
}

NeuralNetwork::NeuralNetwork(std::string path)
{
	//TODO
}

NeuralNetwork::~NeuralNetwork()
{
//	for (int i = 0; i < layers; i++) {
//		delete weights[i];
//		delete biases[i];
//	}

	delete [] weights;
	delete[] biases;
}

Vector NeuralNetwork::feedForward(const Vector& input)
{
	Vector result = input;
	for (int i = 0; i < layers; i++) 
		result = weights[i] * result + biases[i];
	return result;
}

