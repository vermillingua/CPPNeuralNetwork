
#include "Vector.h"
#include <limits>

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

Vector::Vector(std::initializer_list<double> input)
{
	this->length = input.size();
	elements = new double[length];
	for (int i = 0; i < length; i++) 
		elements[i] = input.begin()[i];
}

void Vector::setLength(int length)
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

void Vector::map(double (*foo)(double))
{
	for (int i = 0; i < length; i++)
		set(i, foo(get(i)));
}

Vector operator*(const Vector& left, const Vector& right)
{
	if(left.length != right.length)
		throw std::runtime_error("Invalid vector dimentions for multiplication!");
	
	Vector result(left.length);
	for (int i = 0; i < result.length; i++)
		result.elements[i] = left.elements[i] + right.elements[i];
	return result;
}

Vector operator*(const Vector& left, const double& right)
{
	Vector result(left.length);
	for (int i = 0; i < result.length; i++) 
		result.elements[i] = left.elements[i] * right;
	return result;
}

Vector operator*(const Matrix& left, const Vector& right)
{
	if(left.getCols() != right.length)
		throw std::runtime_error("Invalid dimentions for Matrix and Vector multiplication!");
	
	Vector result(left.getRows(), 0);
	for (int r = 0; r < result.length; r++) 
		for (int c = 0; c < right.length; c++)
			result.elements[r] += left.get(r, c) * right.get(c);
	return result;
}

Vector operator+(const Vector& left, const Vector& right)
{
	if(left.length != right.length)
		throw std::runtime_error("Invalid vector dimentions for addition!");
	
	Vector result(left.length);
	for (int i = 0; i < result.length; i++) 
		result.elements[i] = left.elements[i] + right.elements[i];
	return result;
}


Vector operator+(const Vector& left, const double& right)
{
	Vector result(left.length);
	for (int i = 0; i < result.length; i++) 
		result.elements[i] = left.elements[i] + right;
	return result;
}

Vector operator-(const Vector& left, const Vector& right)
{
	if(left.length != right.length)
		throw std::runtime_error("Invalid vector dimentions for subtraction!");
	
	Vector result(left.length);
	for (int i = 0; i < result.length; i++) 
		result.elements[i] = left.elements[i] - right.elements[i];
	return result;
}


Vector operator-(const Vector& left, const double& right)
{
	Vector result(left.length);
	for (int i = 0; i < result.length; i++) 
		result.elements[i] = left.elements[i] - right;
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


std::ostream& operator<<(std::ostream& cout, const Vector& vector)
{
	cout << "[";

	for (int i = 0; i < vector.length - 1; i++) 
		cout << vector.elements[i] << ", ";

	cout << vector.elements[vector.length - 1] << "]\n";
	return cout;
}
