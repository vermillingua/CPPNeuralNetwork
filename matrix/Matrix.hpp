
#ifndef MATRIX_HPP
#define MATRIX_HPP

struct Matrix
{
private:
	double* matrix;
	int rows;
	int cols;

public:
	Matrix(int rows, int cols);
	~Matrix();
};

static Matrix* generateMatrix(int rows, int cols);

#endif /* MATRIX_HPP */
