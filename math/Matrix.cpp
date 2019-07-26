
#include "Matrix.h"

#include <cstddef>

Matrix::Matrix(): m_rows(0), m_cols(0), m_elements(NULL) {}

Matrix::Matrix(int rows, int cols): m_rows(rows), m_cols(cols)
{
	m_elements = new data_type[size()];
}

Matrix::Matrix(int rows, int cols, data_type value): Matrix(rows, cols)
{
	std::fill(m_elements, m_elements + size(), value);
}

Matrix::Matrix(const Matrix& other): Matrix(other.m_rows, other.m_cols)
{
	std::copy(other.m_elements, other.m_elements + size(), m_elements);
}

Matrix::Matrix(std::initializer_list<std::initializer_list<data_type> > input)
{
	int rows = input.size();
	if(rows > 0)
	{
		int cols = input.begin()->size();

		this->m_rows = rows;
		this->m_cols = cols;
		m_elements = new data_type[size()];

		for (int r = 0; r < rows; r++) {
			if(input.begin()[r].size() != cols)
				throw std::runtime_error("All matrix columns must be the same size!");
			for (int c = 0; c < cols; c++)
				set(r, c, input.begin()[r].begin()[c]);
		}
	}
}

void Matrix::set_dimensions(int rows, int cols)
{
	if(this->m_rows != rows || this->m_cols != cols)
	{
		this->m_rows = rows;
		this->m_cols = cols;
		delete[] m_elements;
		m_elements = new data_type[size()];
	}
}

Matrix::~Matrix()
{
	delete[] m_elements;
}

Matrix Matrix::transpose() const
{
	Matrix result(m_cols, m_rows);

	for (int r = 0; r < m_rows; r++)
		for (int c = 0; c < m_cols; c++)
			result.set(c, r, get(r, c));

	return result;
}

Matrix& Matrix::map(data_type (*foo)(data_type))
{
	for (int i = 0; i < size(); i++)
		m_elements[i] = foo(m_elements[i]);
	return *this;
}

Matrix operator*(const Matrix& left, const Matrix& right)
{
	verify(left.m_cols == right.m_rows,
		"Invalid dimensions for multiplication!");

	Matrix result(left.m_rows, right.m_cols);
	for (int r = 0; r < result.m_rows; r++)
	{
		for (int c = 0; c < result.m_cols; c++)
		{
			data_type sum = 0;
			for (int i = 0; i < left.m_cols; i++)
				sum += left.get(r, i) * right.get(i, c);
			result.set(r, c, sum);
		}
	}
	return result;
}

Matrix operator*(const Matrix& left, const data_type& right)
{
	Matrix result(left.m_rows, left.m_cols);
	for (int i = 0; i < result.size(); i++)
		result.m_elements[i] = left.m_elements[i] * right;
	return result;
}

Matrix operator+(const Matrix& left, const Matrix& right)
{
	verify(left.m_rows == right.m_rows && left.m_cols == right.m_cols,
		"Invalid dimentions for addition!");

	Matrix result(left.m_rows, left.m_cols);
	for (int i = 0; i < result.size(); i++)
		result.m_elements[i] = left.m_elements[i] + right.m_elements[i];
	return result;
}

Matrix operator+(const Matrix& left, const data_type& right)
{
	Matrix result = left;
	for (int i = 0; i < std::min(result.m_cols, result.m_rows); i++)
		result.set(i, i, result.get(i, i) + right);
	return result;
}

Matrix operator-(const Matrix& left, const Matrix& right)
{
	verify(left.m_rows == right.m_rows && left.m_cols == right.m_cols,
		"Invalid dimentions for subtractions!");

	Matrix result(left.m_rows, left.m_cols);
	for(int i = 0; i < result.size(); i++)
		result.m_elements[i] = left.m_elements[i] - right.m_elements[i];
	return result;
}

Matrix operator-(const Matrix& left, const data_type& right)
{
	Matrix result = left;
	for (int i = 0; i < std::min(result.m_cols, result.m_rows); i++)
		result.set(i, i, result.get(i, i) - right);
	return result;
}

Matrix outer_prod(const Vector& right, const Vector& left)
{
	Matrix result(right.m_length, left.m_length);
	for (int r = 0; r < result.m_rows; r++)
		for (int c = 0; c < result.m_cols; c++)
			result.set(r, c, right.get(r) * left.get(c));
	return result;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		set_dimensions(other.m_rows, other.m_cols);
		std::copy(other.m_elements, other.m_elements + other.size(), m_elements);
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	*this = (*this * other);
	return *this;
}

Matrix& Matrix::operator*=(const data_type& other)
{
	for (int i = 0; i < size(); i++)
		m_elements[i] *= other;

	return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	verify(m_rows == other.m_rows && m_cols == other.m_cols,
		"Invalid dimentions for addition!");

	for (int i = 0; i < size(); i++)
		m_elements[i] += other.m_elements[i];
	return *this;
}

Matrix& Matrix::operator+=(const data_type& other)
{
	for (int i = 0; i < std::min(m_rows, m_cols); i++)
		set(i, i, get(i, i) + other);
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	verify(m_rows == other.m_rows && m_cols == other.m_cols,
		"Invalid dimentions for subtractions!");

	for (int i = 0; i < size(); i++)
		m_elements[i] -= other.m_elements[i];
	return *this;
}

Matrix& Matrix::operator-=(const data_type& other)
{
	for (int i = 0; i < std::min(m_rows, m_cols); i++)
		set(i, i, get(i, i) - other);
	return *this;
}

std::ostream& operator<<(std::ostream& cout, const Matrix& matrix)
{
	for (int r = 0; r < matrix.m_rows; r++) {
		cout << "[";
		for (int c = 0; c < matrix.m_cols - 1; c++) {
			cout << matrix.get(r, c) << ", ";
		}
		cout << matrix.get(r, matrix.m_cols - 1) << "]\n";
	}
	return cout;
}

std::ofstream& operator<<(std::ofstream& file, const Matrix& matrix)
{
	file.write((char*)(&matrix.m_rows), sizeof(unsigned int));
	file.write((char*)(&matrix.m_cols), sizeof(unsigned int));
	file.write((char*)matrix.m_elements, sizeof(data_type) * matrix.size());
	return file;
}

std::ifstream& operator>>(std::ifstream& file, Matrix& matrix)
{
	unsigned int r = 0;
	unsigned int c = 0;
	file.read((char*)(&r), sizeof(unsigned int));
	file.read((char*)(&c), sizeof(unsigned int));
	matrix.set_dimensions(r, c);
	file.read((char*)matrix.m_elements, sizeof(data_type) * matrix.size());
	return file;
}
