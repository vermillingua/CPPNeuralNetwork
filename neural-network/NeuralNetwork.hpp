
#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include <string>

#include "../math/Matrix.h"
#include "../math/Vector.h"
#include "../mnist/mnist.h"

struct NeuralNetwork
{
private:
	Matrix* weights;
	Vector* biases;
	unsigned int layers;

	void initialize();

	Vector feedForward(const Vector& input) const;
	void feedForward(Vector weighted_inputs[], Vector activations[]) const;
	void generateErrors(const Vector weighted_inputs[], const Vector activations[], 
		const Vector& target, Vector errors[]) const;
	void updateWeightsAndBiases(const Vector errors[], const Vector activations[], 
		double learningRate);

public:
	
	NeuralNetwork(std::vector<int> layers);
	NeuralNetwork(std::string path);
	~NeuralNetwork();

	std::vector<double> classify(std::vector<double> input) const;

	void train(std::vector<std::vector<double>> input, std::vector<std::vector<double>> output,
		int epochs, double learningRate);

	void saveTo(std::string path) const;
};

void rawToCSV(std::string rawPath, std::string csvDir);

#endif /* NEURALNETWORK_HPP */
