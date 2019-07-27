
#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include <fstream>

#include "../math/LinearAlgebra.h"

struct NeuralNetwork
{
private:
	Matrix* m_weights;
	Vector* m_biases;
	unsigned int m_layers;

	void initialize();

	Vector feed_forward(const Vector& input) const;
	void feed_forward(Vector weighted_inputs[], Vector activations[]) const;
	void generate_errors(const Vector weighted_inputs[], const Vector activations[], 
		const Vector& target, Vector errors[]) const;
	void update_weights_and_biases(const Vector errors[], const Vector activations[], 
		double learningRate);

public:
	
	NeuralNetwork(int layers);
	NeuralNetwork(const std::vector<int>& layers);
	NeuralNetwork(std::ifstream file);
	~NeuralNetwork();

	void operator=(const NeuralNetwork& other);

	int classify(const Vector& input) const;

	void train(const std::vector<Vector>& input, const std::vector<Vector>& output,
		int epochs, double learningRate);

	void save_to(std::ofstream file) const;
};

#endif /* NEURALNETWORK_HPP */
