
#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include "../matrix/Matrix.h"

struct NeuralNetwork
{
private:
	Matrix** weights;
	Matrix** biases;
	int layers;

public:
	NeuralNetwork(int layers, int* layer_sizes);
	~NeuralNetwork();

	Matrix* feedForward(Matrix* input);


};

#endif /* NEURALNETWORK_HPP */
