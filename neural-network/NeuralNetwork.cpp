
#include "NeuralNetwork.hpp"

#include <random>
#include <cmath>
#include <algorithm>

NeuralNetwork::NeuralNetwork(int layers)
{
	m_layers = layers;
	m_weights = new Matrix[m_layers];
	m_biases = new Vector[m_layers];
}

NeuralNetwork::NeuralNetwork(const std::vector<int>& input)
{
	m_layers = input.size() - 1;
	m_weights = new Matrix[m_layers];
	m_biases = new Vector[m_layers];
	for (int i = 0; i < m_layers; i++) 
	{
		m_weights[i] = Matrix(input[i + 1], input[i], 0);
		m_biases[i] = Vector(input[i + 1], 0);
	}
	initialize();
}

NeuralNetwork::NeuralNetwork(std::ifstream file)
{
	if(file.is_open())
	{
		file.read((char*)(&m_layers), sizeof(unsigned int));
		m_weights = new Matrix[m_layers];
		m_biases = new Vector[m_layers];
		for (int i = 0; i < m_layers; i++) 
		{
			file >> m_weights[i];
			file >> m_biases[i];
		}
	}
	else
	{
		std::cerr << "Failed to open neural network file!" << std::endl;
		std::exit(-1);
	}
}

NeuralNetwork::~NeuralNetwork()
{
	delete [] m_weights;
	delete [] m_biases;
}

void NeuralNetwork::operator=(const NeuralNetwork& other)
{
	if(m_layers != other.m_layers)
	{
		delete [] m_weights;
		delete [] m_biases;
		m_layers = other.m_layers;
		m_weights = new Matrix[m_layers];
		m_biases = new Vector[m_layers];
	}

	for (int i = 0; i < m_layers; i++) {
		m_weights[i] = other.m_weights[i];
		m_biases[i] = other.m_biases[i];
	}
}

std::uniform_real_distribution<double> range(-1, 1);
std::default_random_engine engine;

double rand(double x)
{
	return range(engine);
}

void NeuralNetwork::initialize()
{
	for (int i = 0; i < m_layers; i++) {
		m_weights[i].map(rand);
		m_biases[i].map(rand);
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

Vector NeuralNetwork::feed_forward(const Vector& input) const
{
	Vector result = input;
	for (int i = 0; i < m_layers; i++) 
		result = (m_weights[i] * result + m_biases[i]).map(sigmoid);
	return result;
}

void NeuralNetwork::feed_forward(Vector weighted_inputs[], Vector activations[]) const
{
	for (int i = 0; i < m_layers; i++) 
	{
		weighted_inputs[i] = m_weights[i] * activations[i] + m_biases[i];
		activations[i + 1] = weighted_inputs[i];
		activations[i + 1].map(sigmoid);
	}
}

void NeuralNetwork::generate_errors(const Vector weighted_inputs[], const Vector activations[], 
	const Vector& target, Vector errors[]) const
{
	Vector t = weighted_inputs[m_layers - 1];
	errors[m_layers - 1] = Vector::hamming_product(activations[m_layers] - target, t.map(sigmoidPrime));

	for (int i = m_layers - 2; i > -1; i--) 
	{
		Vector temp = weighted_inputs[i];
		errors[i] = Vector::hamming_product(m_weights[i + 1].transpose() * errors[i + 1], temp.map(sigmoidPrime));
	}
}

void NeuralNetwork::update_weights_and_biases(const Vector errors[], const Vector activations[], 
	double learningRate)
{
	for (int i = 0; i < m_layers; i++) 
	{
		m_biases[i] -= errors[i] * learningRate;

		Matrix a = outer_prod(errors[i], activations[i]);
		m_weights[i] = m_weights[i] - (a * learningRate);
	}
}

int NeuralNetwork::classify(const Vector& input) const
{
	return feed_forward(input).max_index();
}

void c_shuffle(int* list, int size)
{
	for (int i = size - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		int t = list[i];
		list[i] = list[j];
		list[j] = t;
	}
}

void NeuralNetwork::train(const std::vector<Vector>& input, 
	const std::vector<Vector>& output, int epochs, double learningRate)
{
	Vector target;

	Vector weighted_inputs[m_layers]; // z
	Vector activations[m_layers + 1]; // a
	Vector errors[m_layers]; // delta

	int list[input.size()];
	for (int i = 0; i < input.size(); i++) 
		list[i] = i;

	srand(time(NULL));
	
	for (int i = 0; i < epochs; i++) 
	{
		c_shuffle(list, input.size());
		for (int j = 0; j < input.size(); j++) 
		{
			int index = list[j];
			activations[0] = input[index];
			target = output[index];
			
			feed_forward(weighted_inputs, activations);
			generate_errors(weighted_inputs, activations, target, errors);
			update_weights_and_biases(errors, activations, learningRate);
		}
	}
}

void NeuralNetwork::save_to(std::ofstream file) const
{
	file.write((char*)(&m_layers), sizeof(unsigned int));
	for (int i = 0; i < m_layers; i++) 
	{
		file << m_weights[i];
		file << m_biases[i];
	}
	file.flush();
}
