
#ifndef MNIST_H
#define MNIST_H

#include <fstream>
#include <iostream>
#include <vector>

struct Image
{
private:
	unsigned int label = 0;
	unsigned int rows;
	unsigned int cols;
	unsigned char* pixels;

	inline unsigned char get(int row, int col) const {
		return pixels[row * cols + col];
	}

	inline unsigned int size() const {
		return rows * cols;
	}

	void resize(int rows, int cols);

public:
	
	Image();
	~Image();

	static void loadFile(std::ifstream& file, std::vector<Image>& images);

	Image& center();

	friend std::ostream& operator<<(std::ostream& cout, const Image& image);
	friend std::ifstream& operator>>(std::ifstream& file, Image& image);

};

#endif /* MNIST_H */
