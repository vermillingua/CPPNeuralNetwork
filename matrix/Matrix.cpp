
#include "Matrix.hpp"

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols)
{
	//TODO allocate memory for the matrix ptr	
}

Matrix::~Matrix()
{
	//TODO free memory for the amtrix ptr
}

static Matrix* generateMatrix(int rows, int cols)
{
	//TODO create a new matrix and fill it with random values
	return new Matrix(rows, cols);
}


