
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
	unsigned int rows;
	unsigned int cols;
	double* elements;

	void setDimensions(unsigned int rows, unsigned int cols);

	inline unsigned int size() const {
		return rows * cols;
	}

	inline void set(unsigned int row, unsigned int col, double value) {
		elements[row * cols + col] = value;
	}

	inline double get(unsigned int row, unsigned int col) const {
		return elements[row * cols + col];
	}

public:
	Matrix();
	Matrix(unsigned int rows, unsigned int cols);
	Matrix(unsigned int rows, unsigned int cols, double value);
	Matrix(const Matrix& other);
	Matrix(std::initializer_list<std::initializer_list<double> > input);

	static Matrix identity(unsigned int dimention);

	~Matrix();

	double trace() const;
	Matrix transpose() const;
	//TODO double determinant() const;

	Matrix& map(double (*foo)(double));

	friend Matrix operator*(const Matrix& left, const Matrix& right);
	friend Matrix operator*(const Matrix& left, const double& right);
	friend Matrix operator+(const Matrix& left, const Matrix& right);
	friend Matrix operator+(const Matrix& left, const double& right);
	friend Matrix operator-(const Matrix& left, const Matrix& right);
	friend Matrix operator-(const Matrix& left, const double& right);
	friend Matrix operator^(const Matrix& left, const int& right);

	friend Vector operator*(const Matrix& left, const Vector& right); //Def in Vector.cpp
	friend Matrix operator-(const Matrix& left, const Vector& right);
	friend Matrix mult(const Vector& right, const Vector& left);

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

	std::string get_dimentions() const
	{
		std::stringstream ss;
		ss << "r = " << rows;
		ss << ", c = " << cols;
		return ss.str();
	}
};

#endif /* MATRIX_H */
