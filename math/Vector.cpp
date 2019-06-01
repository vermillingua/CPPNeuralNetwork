
#include "Vector.h"

#include <limits>

#include "Matrix.h"

Vector::Vector(): length(0)
{
	elements = NULL;
}

Vector::Vector(unsigned int length): length(length)
{
	elements = new double[length];
}

Vector::Vector(unsigned int length, double value): length(length)
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

void Vector::setLength(unsigned int length)
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

double Vector::max()
{
	double max = std::numeric_limits<double>::lowest();
	for (int i = 0; i < length; i++)
		if(get(i) > max)
			max = get(i);
	return max;
}

double Vector::min()
{
	double min = std::numeric_limits<double>::max();
	for (int i = 0; i < length; i++)
		if(get(i) < min)
			min = get(i);
	return min;
}

double Vector::sum()
{
	double sum = 0;
	for (int i = 0; i < length; i++)
		sum += get(i);
	return sum;
}

Vector& Vector::map(double (*foo)(double))
{
	std::cout << "test 2" << std::endl;
	for (int i = 0; i < length; i++)
		set(i, foo(get(i)));
	return *this;
}

Vector& Vector::copy() const
{
	std::cout << "test 1" << std::endl;
	Vector result;
	result = *this;
	return result;
}

std::vector<double> Vector::toSTDVector() const //TODO make more efficient
{
	std::vector<double> result(length);
	for (int i = 0; i < length; i++)
		result[i] = get(i);
	return result;
}

Vector operator*(const Vector& left, const Vector& right)
{
	if(left.length != right.length)
		throw std::runtime_error("Invalid vector dimentions for multiplication!");

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


Vector operator+(const Vector& left, const double& right)
{
	Vector result(left.length);
	for (int i = 0; i < result.length; i++)
		result.set(i, left.get(i) + right);
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


Vector operator-(const Vector& left, const double& right)
{
	Vector result(left.length);
	for (int i = 0; i < result.length; i++)
		result.set(i, left.get(i) - right);
	return result;
}

Vector& Vector::operator=(const Vector& other)
{
	if(this != &other)
	{
		setLength(other.length);
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
	vector.setLength(len);
	file.read((char*)vector.elements, (sizeof(double)/sizeof(char)) * vector.length);
	return file;
}
