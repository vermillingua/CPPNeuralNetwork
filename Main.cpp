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
	std::string save_path = "shallow2.nn";

	NeuralNetwork nn(layers); // Create a new nn with the specified layers.
	//NeuralNetwork nn = std::ifstream(save_path); // Load from save_path file.

	stopwatch sw;

	std::cout << "Benchmarking..." << std::endl;
	sw.start();
	double percentage = benchmark(nn, b_input, b_output, b_images);
	sw.stop();
	std::cout << "Finished benchmarking in " << sw << " - " << (percentage * 100) << "% acurate." << std::endl;

	std::cout << "Training..." << std::endl;
	sw.start();
	nn.train(t_input, t_output, 1, .01);
	sw.stop();
	std::cout << "Finished Training in " << sw << std::endl;
	
	std::cout << "Benchmarking..." << std::endl;
	sw.start();
	percentage = benchmark(nn, b_input, b_output, b_images);
	sw.stop();
	std::cout << "Finished benchmarking in " << sw << " - " << (percentage * 100) << "% acurate." << std::endl;

	//nn.save_to(std::ofstream(save_path)); // Save nn to the save_path file.

	return -1;
}
