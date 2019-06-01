
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

	unsigned int batchSize = 10;
	double learningRate = .3;

	void initialize();

	Vector feedForward(const Vector& input) const;
	void feedForward(Vector activations[], Vector weighted_inputs[]) const;
	void generateErrors(const Vector weighted_inputs[], const Vector activations[], 
		const Vector& target, Vector* errors) const;
	void backPropagation(const Vector& inputs, const Vector& target);

public:
	
	void setBatchSize(unsigned int size) {
		batchSize = size;
	}

	void setLearningRate(double rate) {
		learningRate = rate;
	}

	NeuralNetwork(std::vector<int> layers);
	NeuralNetwork(std::string path);
	~NeuralNetwork();

	std::vector<double> classify(std::vector<double> input) const;
	void train(std::vector<std::vector<double>> trainingData, 
		std::vector<std::vector<double>> trainingLabels);

	Vector classify(const Image& image);
	void train(const Image& image);

	void saveTo(std::string path) const;
};

void rawToCSV(std::string rawPath, std::string csvDir);

#endif /* NEURALNETWORK_HPP */
