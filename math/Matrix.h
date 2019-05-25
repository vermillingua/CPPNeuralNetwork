
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <initializer_list>

struct Matrix
{
private:
	int rows;
	int cols;
	double* elements;

	void setDimentions(int rows, int cols);

public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, double value);
	Matrix(std::initializer_list<std::initializer_list<double> > input);

	static Matrix identity(int dimention);

	~Matrix();

	inline int size() const {
		return rows * cols;
	}

	inline int getRows() const {
		return rows;
	}

	inline int getCols() const {
		return cols;
	}

	inline void set(int row, int col, double value) {
		elements[row * cols + col] = value;
	}

	inline double get(int row, int col) const {
		return elements[row * cols + col];
	}

	double trace() const;
	Matrix transpose() const;
	//TODO double determinant() const;

	void map(double (*foo)(double));

	friend Matrix operator*(const Matrix& left, const Matrix& right);
	friend Matrix operator*(const Matrix& left, const int& right);
	friend Matrix operator+(const Matrix& left, const Matrix& right);
	friend Matrix operator+(const Matrix& left, const int& right);
	friend Matrix operator-(const Matrix& left, const Matrix& right);
	friend Matrix operator-(const Matrix& left, const int& right);
	friend Matrix operator^(const Matrix& left, const int& right);

	Matrix& operator=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	Matrix& operator*=(const int& other);
	Matrix& operator+=(const Matrix& other);
	Matrix& operator+=(const int& other);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator-=(const int& other);

	friend std::ostream& operator<<(std::ostream& cout, const Matrix& matrix);
};

#endif /* MATRIX_H */
