
#include "Matrix.hpp"

#include <cstddef>
#include <iostream>

Matrix::Matrix(): rows(0), cols(0)
{
	elements = NULL;
}

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols)
{
	elements = new double[size()];
}

Matrix::Matrix(int rows, int cols, double value): rows(rows), cols(cols)
{
	elements = new double[size()];
	std::fill(elements, elements + size(), value);
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double> > input)
{
	int rows = input.size();
	if(rows > 0)
	{
		int cols = input.begin()->size();

		this->rows = rows;
		this->cols = cols;
		elements = new double[size()];

		for (int r = 0; r < rows; r++) {
			if(input.begin()[r].size() != cols)
				throw std::runtime_error("All matrix columns must be the same size!");
			for (int c = 0; c < cols; c++)
				set(r, c, input.begin()[r].begin()[c]);
		}
	}
}

void Matrix::setDimentions(int rows, int cols)
{
	if(this->rows != rows || this->cols != cols)
	{
		this->rows = rows;
		this->cols = cols;
		delete[] elements;
		elements = new double[size()];
	}
}

Matrix::~Matrix()
{
	delete[] elements;
}

Matrix Matrix::identity(int dimentions)
{
	Matrix result(dimentions, dimentions, 0);
	for (int i = 0; i < dimentions; i++)
		result.set(i, i, 1);
	return result;
}

Matrix operator*(const Matrix& left, const Matrix& right)
{
	if(left.cols != right.rows)
		throw std::runtime_error("Invalid dimentions for multiplication!");
	Matrix result(left.rows, right.cols);

	for (int r = 0; r < result.rows; r++)
	{
		for (int c = 0; c < result.cols; c++)
		{
			double sum = 0;
			for (int i = 0; i < left.cols; i++)
				sum += left.get(r, i) * right.get(i, c);
			result.set(r, c, sum);
		}
	}

	return result;
}

Matrix operator+(const Matrix& left, const Matrix& right)
{
	if(left.size() != right.size())
		throw std::runtime_error("Invalid dimentions for addition!");

	Matrix result(left.rows, left.cols);

	for (int i = 0; i < result.size(); i++)
		result.elements[i] = left.elements[i] + right.elements[i];

	return result;
}

Matrix operator-(const Matrix& left, const Matrix& right)
{
	if(left.size() != right.size())
		throw std::runtime_error("Invalid dimentions for subtraction!");

	Matrix result(left.rows, left.cols);

	for(int i = 0; i < result.size(); i++)
		result.elements[i] = left.elements[i] - right.elements[i];

	return result;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		setDimentions(other.rows, other.cols);
		std::copy(other.elements, other.elements + other.size(), elements);
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	if(cols != other.rows)
		throw std::runtime_error("Invalid dimentions for multiplication!");

	*this = *this * other;
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	if(size() != other.size())
		throw std::runtime_error("Invalid dimentions for addition!");

	for (int i = 0; i < size(); i++)
		elements[i] += other.elements[i];

	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	if(size() != other.size())
		throw std::runtime_error("Invalid dimentions for subtraction!");

	for (int i = 0; i < size(); i++)
		elements[i] -= other.elements[i];

	return *this;
}

std::ostream& operator<<(std::ostream& cout, const Matrix& matrix)
{
	for (int r = 0; r < matrix.rows; r++) {
		cout << "[";
		for (int c = 0; c < matrix.cols - 1; c++) {
			cout << matrix.get(r, c) << ", ";
		}
		cout << matrix.get(r, matrix.cols - 1) << "]\n";
	}
	return cout;
}
