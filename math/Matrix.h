
#ifndef MATRIX_H
#define MATRIX_H

#include "LinearAlgebra.h"

#include <fstream>
#include <initializer_list>

struct Vector;

struct Matrix
{
	friend Vector;
	
private:
	int m_rows;
	int m_cols;
	data_type* m_elements;

	void set_dimensions(int rows, int cols);

	inline int size() const {
		return m_rows * m_cols;
	}

	inline void set(int row, int col, data_type value) {
		m_elements[row * m_cols + col] = value;
	}

	inline data_type get(int row, int col) const {
		return m_elements[row * m_cols + col];
	}

public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, data_type value);
	Matrix(const Matrix& other);
	Matrix(std::initializer_list<std::initializer_list<data_type> > input);

	~Matrix();

	Matrix transpose() const;

	Matrix& map(data_type (*foo)(data_type));

	friend Matrix operator*(const Matrix& left, const Matrix& right);
	friend Matrix operator*(const Matrix& left, const data_type& right);
	friend Matrix operator+(const Matrix& left, const Matrix& right);
	friend Matrix operator+(const Matrix& left, const data_type& right);
	friend Matrix operator-(const Matrix& left, const Matrix& right);
	friend Matrix operator-(const Matrix& left, const data_type& right);

	friend Vector operator*(const Matrix& left, const Vector& right); //Def in Vector.cpp
	friend Matrix outer_prod(const Vector& right, const Vector& left);

	Matrix& operator=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	Matrix& operator*=(const data_type& other);
	Matrix& operator+=(const Matrix& other);
	Matrix& operator+=(const data_type& other);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator-=(const data_type& other);

	friend std::ostream& operator<<(std::ostream& cout, const Matrix& matrix);
	friend std::ofstream& operator<<(std::ofstream& file, const Matrix& matrix);
	friend std::ifstream& operator>>(std::ifstream& file, Matrix& matrix);
};

#endif /* MATRIX_H */
