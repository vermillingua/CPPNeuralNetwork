
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <initializer_list>

struct Vector;

struct Matrix
{
private:
	int rows;
	int cols;
	double* elements;

	void set_dimensions(int rows, int cols);

	inline int size() const {
		return rows * cols;
	}

	inline void set(int row, int col, double value) {
		elements[row * cols + col] = value;
	}

	inline double get(int row, int col) const {
		return elements[row * cols + col];
	}

public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, double value);
	Matrix(const Matrix& other);
	Matrix(std::initializer_list<std::initializer_list<double> > input);

	~Matrix();

	Matrix transpose() const;

	Matrix& map(double (*foo)(double));

	friend Matrix operator*(const Matrix& left, const Matrix& right);
	friend Matrix operator*(const Matrix& left, const double& right);
	friend Matrix operator+(const Matrix& left, const Matrix& right);
	friend Matrix operator+(const Matrix& left, const double& right);
	friend Matrix operator-(const Matrix& left, const Matrix& right);
	friend Matrix operator-(const Matrix& left, const double& right);

	friend Vector operator*(const Matrix& left, const Vector& right); //Def in Vector.cpp
	friend Matrix outer_prod(const Vector& right, const Vector& left);

	Matrix& operator=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	Matrix& operator*=(const double& other);
	Matrix& operator+=(const Matrix& other);
	Matrix& operator+=(const double& other);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator-=(const double& other);

	friend std::ostream& operator<<(std::ostream& cout, const Matrix& matrix);
	friend std::ofstream& operator<<(std::ofstream& file, const Matrix& matrix);
	friend std::ifstream& operator>>(std::ifstream& file, Matrix& matrix);
};

#endif /* MATRIX_H */
