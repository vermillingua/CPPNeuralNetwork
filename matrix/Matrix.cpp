
#include "Matrix.hpp"

#include <sstream>
// #include <iostream>

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols)
{
	matrix = new double[rows * cols];
}

Matrix::~Matrix()
{
	delete [] matrix;
}

void Matrix::fill(double value)
{
	for (int i = 0; i < rows * cols; i++)
		this->matrix[i] = value;
}

void Matrix::add(Matrix* matrix) // Add check for correct dimentions?
{
	for (int i = 0; i < rows * cols; i++) 
		this->matrix[i] += matrix->matrix[i];
}

void Matrix::mult(Matrix* matrix) // Add check for correct dimetions?
{
	for (int i = 0; i < rows * cols; i++)
		this->matrix[i] *= matrix->matrix[i];
}

Matrix* Matrix::dotProd(Matrix* a, Matrix* b)
{
	Matrix* result = new Matrix(a->getRows(), b->getCols());
	//TODO Actually implement. Althought we might not need it.
	return result;
}

std::string Matrix::str()
{
	std::stringstream ss;
	
	for (int r = 0; r < getRows(); r++) 
	{
		ss << "[";
		for (int c = 0; c < getCols() - 1; c++) 
			ss << get(r, c) << ", ";
		ss << get(r, getCols() - 1) << "]\n";
	}

	return ss.str();
}
