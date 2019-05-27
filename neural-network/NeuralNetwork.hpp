
#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include <string>

#include "../math/Matrix.h"
#include "../math/Vector.h"

struct NeuralNetwork
{
private:
	Matrix* weights;
	Vector* biases;
	unsigned int layers;

	unsigned int batchSize = 10;
	double learningRate = 0.01;

	Vector feedForward(const Vector& input);
	double cost(Vector* input);
	void backTracking();

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

	std::vector<double> classify(std::vector<double> input);
	void train(std::vector<std::vector<double>> trainingData, 
		std::vector<std::vector<double>> trainingLabels);
	void saveTo(std::string path);
};

void rawToCSV(std::string rawPath, std::string csvDir);

#endif /* NEURALNETWORK_HPP */
