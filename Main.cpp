#include <iostream>
#include <random>

#include "neural-network/NeuralNetwork.hpp"
#include "stopwatch/stopwatch.h"
#include "mnist/mnist.h"

#include "math/Vector.h"

using namespace sw;

void load_files(std::vector<Vector>& input, std::vector<Vector>& output,
	std::vector<Image>& images, std::string image_file_path, std::string label_file_path)
{
	std::ifstream image_file(image_file_path);
	std::ifstream label_file(label_file_path);

	Image::loadFiles(image_file, label_file, images);

	input.resize(images.size());
	output.resize(images.size());

	for (int i = 0; i < images.size(); i++) 
	{
		input[i] = images[i].toVector();
		output[i] = Vector(10, 0.0);
		output[i][images[i].getLabel()] = 1;
	}
}

double benchmark(NeuralNetwork& nn, std::vector<Vector>& input,
	std::vector<Vector>& output, std::vector<Image>& images)
{
	int total = images.size();
	int correct = 0;

	for (int i = 0; i < total; i++) {
		int m = nn.classify(input[i]);

		if(m == images[i].getLabel())
			correct++;
	}
	return (double)correct / total;
}

const std::string train_images = "mnist-data/train-images-idx3-ubyte";
const std::string train_labels = "mnist-data/train-labels-idx1-ubyte";
const std::string test_images = "mnist-data/t10k-images-idx3-ubyte";
const std::string test_labels = "mnist-data/t10k-labels-idx1-ubyte";

int main(int argc, char** argv)
{
	std::cout << "Loading files..." << std::endl;
	std::vector<Vector> t_input, t_output;
	std::vector<Image> t_images;
	load_files(t_input, t_output, t_images, 
		train_images, train_labels);

	std::vector<Vector> b_input, b_output;
	std::vector<Image> b_images;
	load_files(b_input, b_output, b_images, 
		test_images, test_labels);
	std::cout << "Finished loading files." << std::endl;

	std::vector<int> layers = {784, 16, 16, 10};
	std::string save_path = "shallow6.nn";

	int epochs = 20;
	double learning_rate = 0.1;
	double learning_rate_rate = 0.5;
	int forgiveness = 1;

	NeuralNetwork nn(layers); // Create a new nn with the specified layers.
	//NeuralNetwork nn = std::ifstream(save_path); // Load from save_path file.

	stopwatch sw;
	NeuralNetwork temp_nn(layers);
	temp_nn = nn;
	int forg = 0;

	std::cout << "Initial Benchmark..." << std::endl;
	sw.start();
	double p1 = benchmark(nn, b_input, b_output, b_images);
	sw.stop();
	std::cout << "Inital accuracy " << (p1 * 100) << "%" << std::endl;

	for (int i = 0; i < epochs; i++) 
	{
		//std::cout << benchmark(nn, b_input, b_output, b_images) << std::endl;
		std::cout << "Training (" << (i + 1) << " of " << epochs << ")..." << std::endl;
		sw.start();
		nn.train(t_input, t_output, 1, learning_rate);
		double p2 = benchmark(nn, b_input, b_output, b_images);
		sw.stop();
		std::cout << "Finished in " << sw.get_total_str() << " - " << (p2 * 100) << "% accuracy" << std::endl;
		if(p2 >= p1)
		{
			p1 = p2;
			temp_nn = nn;
			forg = 0;
			nn.save_to(std::ofstream(save_path));
		}
		else
		{
			std::cout << "Lost accuracy. Forgiveness left " << (forgiveness - forg) << std::endl;
			forg++;
			if(forg > forgiveness)
			{
				nn = temp_nn;
				forg = 0;
				learning_rate *= learning_rate_rate;
				std::cout << "Reverting NN. Changing learning rate to " << learning_rate << std::endl;
			}
		}
	}

	return -1;
}
