
#ifndef MNIST_H
#define MNIST_H

#include <fstream>
#include <iostream>
#include <vector>

struct Image
{
private:
	int label;
	int rows;
	int cols;
	unsigned char* pixels;

	inline char get(int row, int col) const {
		return pixels[row * cols + col];
	}

	inline int size() const {
		return rows * cols;
	}

	void resize(int rows, int cols);

public:
	
	Image();
	~Image();

	int getLabel() const {
		return label;
	}

	static void loadFiles(std::ifstream& imageFile, std::ifstream& labelFile, std::vector<Image>& images);

	std::vector<double> toVector() const;

	friend std::ostream& operator<<(std::ostream& cout, const Image& image);
	friend std::ifstream& operator>>(std::ifstream& file, Image& image);

};

#endif /* MNIST_H */
