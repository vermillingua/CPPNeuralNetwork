
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <fstream>
#include <initializer_list>
#include <vector>

#include "../mnist/mnist.h"

//struct Image;

struct Matrix;

struct Vector
{
private:
	unsigned int length;
	double* elements;

	void setLength(unsigned int length);

	inline double get(unsigned int pos) const {
		return elements[pos];
	}

	inline void set(unsigned int pos, double value) {
		elements[pos] = value;
	}

public:
	Vector();
	Vector(unsigned int length);
	Vector(unsigned int length, double value);
	Vector(const Vector& other);
	Vector(const std::vector<double> other);
	Vector(std::initializer_list<double> input);

	~Vector();

	double max();
	double min();
	double sum();

	Vector& map(double (*foo)(double));
	Vector& copy() const;

	std::vector<double> toSTDVector() const;

	friend Vector operator*(const Vector& right, const Vector& left);
	friend Vector operator*(const Vector& right, const double& left);
	friend Vector operator+(const Vector& right, const Vector& left);
	friend Vector operator+(const Vector& right, const double& left);
	friend Vector operator-(const Vector& right, const Vector& left);
	friend Vector operator-(const Vector& right, const double& left);

	friend Vector operator*(const Matrix& right, const Vector& left);
	friend Matrix operator-(const Matrix& right, const Vector& left); //def in Matrix.h

	friend Vector Image::toVector() const;

	Vector& operator=(const Vector& other);
	Vector& operator-=(const Vector& other);

	friend std::ostream& operator<<(std::ostream& cout, const Vector& vector);
	friend std::ofstream& operator<<(std::ofstream& file, const Vector& vector);
	friend std::ifstream& operator>>(std::ifstream& file, Vector& vector);

};

#endif /* VECTOR_H */
