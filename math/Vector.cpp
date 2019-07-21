
#include "Vector.h"

#include <limits>

#include "Matrix.h"

Vector::Vector(): length(0)
{
	elements = NULL;
}

Vector::Vector(int length): length(length)
{
	elements = new double[length];
}

Vector::Vector(int length, double value): length(length)
{
	elements = new double[length];
	std::fill(elements, elements + length, value);
}

Vector::Vector(const Vector& other)
{
	this->length = other.length;
	elements = new double[length];
	std::copy(other.elements, other.elements + length, elements);
}

Vector::Vector(std::vector<double> input)
{
	this->length = input.size();
	elements = new double[length];
	std::copy(input.begin(), input.end(), elements);
}

Vector::Vector(std::initializer_list<double> input)
{
	this->length = input.size();
	elements = new double[length];
	std::copy(input.begin(), input.end(), elements);
}

void Vector::set_length(int length)
{
	if(this->length != length)
	{
		this->length = length;
		delete [] elements;
		elements = new double[length];
	}
}

Vector::~Vector()
{
	delete [] elements;
}

Vector& Vector::map(double (*foo)(double))
{
	for (int i = 0; i < length; i++)
		set(i, foo(get(i)));
	return *this;
}

std::vector<double> Vector::to_std_vector() const 
{
	std::vector<double> result(length);
	std::copy(elements, elements + length, result.begin());
	return result;
}

Vector Vector::hamming_product(const Vector& right, const Vector& left)
{
	if(right.length != right.length)
		throw std::runtime_error("Invalid vector dimentions for hamming product");
	Vector result(left.length);
	for (int i = 0; i < result.length; i++)
		result.set(i, left.get(i) * right.get(i));
	return result;
}

Vector operator*(const Vector& left, const double& right)
{
	Vector result(left.length);
	for (int i = 0; i < result.length; i++)
		result.set(i, left.get(i) * right);
	return result;
}

Vector operator*(const Matrix& left, const Vector& right)
{
	if(left.cols != right.length)
		throw std::runtime_error("Invalid dimentions for Matrix and Vector multiplication!");

	Vector result(left.rows, 0);
	for (int r = 0; r < result.length; r++)
		for (int c = 0; c < right.length; c++)
			result.elements[r] += left.get(r, c) * right.get(c); //Change to set()
	return result;
}

Vector operator+(const Vector& left, const Vector& right)
{
	if(left.length != right.length)
		throw std::runtime_error("Invalid vector dimentions for addition!");

	Vector result(left.length);
	for (int i = 0; i < result.length; i++)
		result.set(i, left.get(i) + right.get(i));
	return result;
}

Vector operator-(const Vector& left, const Vector& right)
{
	if(left.length != right.length)
		throw std::runtime_error("Invalid vector dimentions for subtraction!");

	Vector result(left.length);
	for (int i = 0; i < result.length; i++)
		result.set(i, left.get(i) - right.get(i));
	return result;
}

Vector& Vector::operator=(const Vector& other)
{
	if(this != &other)
	{
		set_length(other.length);
		std::copy(other.elements, other.elements + length, elements);
	}
	return *this;
}

Vector& Vector::operator-=(const Vector& other)
{
	if(length != other.length)
		throw std::runtime_error("Invalid vector dimentsion for subtraction!");
	
	for (int i = 0; i < length; i++) 
		elements[i] -= other.elements[i];
	
	return *this;
}


std::ostream& operator<<(std::ostream& cout, const Vector& vector)
{
	cout << "[";

	for (int i = 0; i < vector.length - 1; i++)
		cout << vector.get(i) << ", ";

	cout << vector.get(vector.length - 1) << "]\n";
	return cout;
}

std::ofstream& operator<<(std::ofstream& file, const Vector& vector)
{
	file.write((char*)(&vector.length), sizeof(unsigned int)/sizeof(char));
	file.write((char*)vector.elements, (sizeof(double)/sizeof(char)) * vector.length);
	return file;
}

std::ifstream& operator>>(std::ifstream& file, Vector& vector)
{
	int len = 0;
	file.read((char*)(&len), sizeof(unsigned int)/sizeof(char));
	vector.set_length(len);
	file.read((char*)vector.elements, (sizeof(double)/sizeof(char)) * vector.length);
	return file;
}
