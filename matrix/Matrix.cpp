
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

void Matrix::map(double (*foo)(double))
{
	for (int i = 0; i < size(); i++) 
		matrix[i] = foo(matrix[i]);
}

void Matrix::add(Matrix* matrix) 
{
	if(this->size() != matrix->size())
		throw std::runtime_error("Matrices must be the same size for them to be added!");
	for (int i = 0; i < size(); i++) 
		this->matrix[i] += matrix->matrix[i];
}

void Matrix::mult(Matrix* matrix) 
{
	if(this->size() != matrix->size())
		throw std::runtime_error("Matrices must be the same size for them to be multiplied!");
	for (int i = 0; i < size(); i++) 
		this->matrix[i] *= matrix->matrix[i];
}

Matrix* Matrix::dotProd(Matrix* a, Matrix* b)
{
	if(a->getCols() != b->getRows())
		throw std::runtime_error("Matrices must be the correct size to calculate their dot product!");
	Matrix* result = new Matrix(a->getRows(), b->getCols());

	for (int r = 0; r < result->getRows(); r++)
	{
		for (int c = 0; c < result->getCols(); c++)
		{
			double sum = 0;
			for (int i = 0; i < a->getCols(); i++)
				sum += a->get(r, i) * b->get(i, c);
			result->set(r, c, sum);
		}
	}

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
