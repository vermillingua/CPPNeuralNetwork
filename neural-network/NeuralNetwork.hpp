
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

	void initialize();

	Vector feedForward(const Vector& input) const;
	static double cost(const Vector& actual, const Vector& desired);
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

	std::vector<double> classify(std::vector<double> input) const; //May be a problem since output vector may not be the correct size
	void train(std::vector<std::vector<double>> trainingData, 
		std::vector<std::vector<double>> trainingLabels);
	void saveTo(std::string path) const;
};

void rawToCSV(std::string rawPath, std::string csvDir);

#endif /* NEURALNETWORK_HPP */
