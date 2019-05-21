
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

public:
	Matrix(int rows, int cols);
	~Matrix();

	int getRows() {
		return rows;
	}
	
	int getCols() {
		return cols;
	}

	void fill(double value);
	void add(Matrix* matrix);
	void mult(Matrix* matrix);
	static Matrix* dotProd(Matrix* a, Matrix* b);

	std::string str();
};

#endif /* MATRIX_HPP */
