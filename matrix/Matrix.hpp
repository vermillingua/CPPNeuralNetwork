
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <initializer_list>

struct Matrix
{
private:
	int rows;
	int cols;
	double* elements;

	inline int size() const {
		return rows * cols;
	}

	inline void set(int row, int col, double value) {
		elements[row * cols + col] = value;
	}

	inline double get(int row, int col) const {
		return elements[row * cols + col];
	}

	void setDimentions(int rows, int cols);

public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, double value);
	Matrix(std::initializer_list<std::initializer_list<double> > input);

	static Matrix identity(int dimention);

	~Matrix();

	friend Matrix operator*(const Matrix& left, const Matrix& right);
	friend Matrix operator+(const Matrix& left, const Matrix& right);
	friend Matrix operator-(const Matrix& left, const Matrix& right);

	Matrix& operator=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);

	friend std::ostream& operator<<(std::ostream& cout, const Matrix& matrix);
};

#endif /* MATRIX_HPP */
