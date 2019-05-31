
#include "mnist.h"

#include <cstdint>

#include "../math/Vector.h"

Image::Image(): label(0), rows(0), cols(0)
{
	pixels = NULL;
}

Image::~Image()
{
	delete [] pixels;
}

void Image::resize(int r, int c)
{
	if(this->rows != r || this->cols != c)
	{
		this->rows = r;
		this->cols = c;
		delete [] pixels;
		pixels = new unsigned char[size()];
	}
}

int reverseInt (int i)
{
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void Image::loadFile(std::ifstream& file, std::vector<Image>& images)
{
	int32_t magic = 0;
	file.read((char*)(&magic), sizeof(int32_t));
	magic = reverseInt(magic);

	int32_t number_of_images = 0;
	file.read((char*)(&number_of_images), sizeof(int32_t));
	number_of_images = reverseInt(number_of_images);

	int32_t n_rows = 0;
	file.read((char*)(&n_rows), sizeof(int32_t));
	n_rows = reverseInt(n_rows);

	int32_t n_cols = 0;
	file.read((char*)(&n_cols), sizeof(int32_t));
	n_cols = reverseInt(n_cols);

	std::cout << "Loading " << number_of_images << " images..." << std::endl;

	images.resize(number_of_images);

	for (int i = 0; i < number_of_images; i++) 
		file >> images[i];

	std::cout << "Finished loaded images!" << std::endl;
}

Image& Image::center()
{
	//TODO Use center of mass to center custom images. MNIST ones are already centered.
	return *this;
}

Vector Image::toVector() const
{
	Vector result(size());
	
	for (int i = 0; i < size(); i++) 
		result.set(i, pixels[i]);
	
	return result;
}

std::ostream& operator<<(std::ostream& cout, const Image& image)
{
	for (int r = 0; r < image.rows; r++) 
	{
		for (int c = 0; c < image.cols; c++) 
		{
			if(image.get(r, c) > 127)
				cout << '#';
			else if(image.get(r, c) > 0)
				cout << '.';
			else
				cout << ' ';
			cout << ' ';
		}
		cout << '\n';
	}
	return cout;
}

std::ifstream& operator>>(std::ifstream& file, Image& image)
{
	image.resize(28, 28);
	file.read((char*)image.pixels, image.size());
	return file;
}

