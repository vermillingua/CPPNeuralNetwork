
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>

struct Matrix
{
private:
	double* matrix;
	int rows;
	int cols;

	double get(int row, int col) {
		return matrix[row * cols + col];
	}

	void set(int row, int col, double value) {
		matrix[row * cols + col] = value;
	}	

	int size() {
		return rows * cols;
	}

	int getRows() {
		return rows;
	}
	
	int getCols() {
		return cols;
	}

public:
	Matrix(int rows, int cols);
	~Matrix();

	void map(double (*foo)(double));

	void add(Matrix* matrix);
	void mult(Matrix* matrix);
	static Matrix* dotProd(Matrix* a, Matrix* b);

	std::string str();
};

#endif /* MATRIX_HPP */
