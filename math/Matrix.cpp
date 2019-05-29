
#include "Matrix.h"

#include <cstddef>

Matrix::Matrix(): rows(0), cols(0)
{
	elements = NULL;
}

Matrix::Matrix(unsigned int rows, unsigned int cols): rows(rows), cols(cols)
{
	elements = new double[size()];
}

Matrix::Matrix(unsigned int rows, unsigned int cols, double value): rows(rows), cols(cols)
{
	elements = new double[size()];
	std::fill(elements, elements + size(), value);
}

Matrix::Matrix(const Matrix& other)
{
	elements = new double[other.size()];
	std::copy(other.elements, other.elements + size(), elements);
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

void Matrix::setDimensions(unsigned int rows, unsigned int cols)
{
	if(this->rows != rows || this->cols != cols)
	{
		this->rows = rows;
		this->cols = cols;
		delete[] elements;
		elements = new double[size()];
	}
}

Matrix Matrix::identity(unsigned int dimensions)
{
<<<<<<< HEAD
	Matrix result(dimentions, dimentions, 0);
	for (int i = 0; i < dimentions; i++)
=======
	Matrix result(dimensions, dimensions, 0);
	for (int i = 0; i < dimensions; i++)
>>>>>>> 91cc873aba0fc498be9ce1fd26d124425857681a
		result.set(i, i, 1);
	return result;
}

Matrix::~Matrix()
{
	delete[] elements;
}

double Matrix::trace() const
{
	double sum = 0;
	for (int i = 0; i < std::min(rows, cols); i++)
		sum += get(i, i);
	return sum;
}

Matrix Matrix::transpose() const
{
	Matrix result(cols, rows);

	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			result.set(c, r, get(r, c));

	return result;
}

Matrix& Matrix::map(double (*foo)(double))
{
	for (int i = 0; i < size(); i++)
		elements[i] = foo(elements[i]);
	return *this;
}

Matrix operator*(const Matrix& left, const Matrix& right)
{
	if(left.cols != right.rows)
		throw std::runtime_error("Invalid dimensions for multiplication!");
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

Matrix operator*(const Matrix& left, const int& right)
{
	Matrix result(left.rows, left.cols);

	for (int i = 0; i < result.size(); i++)
		result.elements[i] = left.elements[i] * right;

	return result;
}

Matrix operator+(const Matrix& left, const Matrix& right)
{
	if(left.rows == right.rows && left.cols == right.cols)
		throw std::runtime_error("Invalid dimensions for addition!");

	Matrix result(left.rows, left.cols);

	for (int i = 0; i < result.size(); i++)
		result.elements[i] = left.elements[i] + right.elements[i];

	return result;
}

Matrix operator+(const Matrix& left, const int& right)
{
	Matrix result = left;

	for (int i = 0; i < std::min(result.cols, result.rows); i++)
		result.set(i, i, result.get(i, i) + right);

	return result;
}

Matrix operator-(const Matrix& left, const Matrix& right)
{
<<<<<<< HEAD
	if(left.size() != right.size())
		throw std::runtime_error("Invalid dimentions for subtraction!");
=======
	if(left.rows == right.rows && left.cols == right.cols)
		throw std::runtime_error("Invalid dimensions for subtraction!");
>>>>>>> 91cc873aba0fc498be9ce1fd26d124425857681a

	Matrix result(left.rows, left.cols);

	for(int i = 0; i < result.size(); i++)
		result.elements[i] = left.elements[i] - right.elements[i];

	return result;
}

Matrix operator-(const Matrix& left, const int& right)
{
	Matrix result = left;

	for (int i = 0; i < std::min(result.cols, result.rows); i++)
		result.set(i, i, result.get(i, i) - right);

	return result;
}

Matrix operator^(const Matrix& left, const int& right)
{
	Matrix result;
	result = left;

	for (int i = 0; i < right - 1; i++)
		result *= left;

	return result;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		setDimensions(other.rows, other.cols);
		std::copy(other.elements, other.elements + other.size(), elements);
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	*this = (*this * other);
	return *this;
}

Matrix& Matrix::operator*=(const int& other)
{
	for (int i = 0; i < size(); i++)
		elements[i] *= other;

	return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	if(rows == other.rows && cols == other.cols)
		throw std::runtime_error("Invalid dimensions for addition!");

	for (int i = 0; i < size(); i++)
		elements[i] += other.elements[i];

	return *this;
}

Matrix& Matrix::operator+=(const int& other)
{
	for (int i = 0; i < std::min(rows, cols); i++)
		set(i, i, get(i, i) + other);

	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
<<<<<<< HEAD
	if(size() != other.size())
		throw std::runtime_error("Invalid dimentions for subtraction!");
=======
	if(rows == other.rows && cols == other.cols)
		throw std::runtime_error("Invalid dimensions for subtraction!");
>>>>>>> 91cc873aba0fc498be9ce1fd26d124425857681a

	for (int i = 0; i < size(); i++)
		elements[i] -= other.elements[i];

	return *this;
}

Matrix& Matrix::operator-=(const int& other)
{
	for (int i = 0; i < std::min(rows, cols); i++)
		set(i, i, get(i, i) - other);

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

std::ofstream& operator<<(std::ofstream& file, const Matrix& matrix)
{
	file.write((char*)(&matrix.rows), sizeof(unsigned int));
	file.write((char*)(&matrix.cols), sizeof(unsigned int));
	file.write((char*)matrix.elements, sizeof(double) * matrix.size());
	return file;
}

std::ifstream& operator>>(std::ifstream& file, Matrix& matrix)
{
	unsigned int r = 0;
	unsigned int c = 0;
	file.read((char*)(&r), sizeof(unsigned int));
	file.read((char*)(&c), sizeof(unsigned int));
	matrix.setDimensions(r, c);
	file.read((char*)matrix.elements, sizeof(double) * matrix.size());
	return file;
}
