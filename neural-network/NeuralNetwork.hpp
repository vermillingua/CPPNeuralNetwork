
#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include "../math/Matrix.h"
#include "../math/Vector.h"

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
