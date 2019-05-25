
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>

#include "Matrix.h"

struct Vector
{
private:
	int length;
	double* elements;
	
	void setLength(int length);

public:
	Vector();
	Vector(int length);
	Vector(int length, double value);
	Vector(std::initializer_list<double> input);

	~Vector();

	inline double get(int pos) const {
		return elements[pos];
	}

	inline void set(int pos, double value) {
		elements[pos] = value;
	}

	inline int getLength() const {
		return this->length;
	}

	double max();
	double min();

	void map(double (*foo)(double));

	friend Vector operator*(const Vector& right, const Vector& left);
	friend Vector operator*(const Vector& right, const double& left);
	friend Vector operator*(const Matrix& right, const Vector& left);
	friend Vector operator+(const Vector& right, const Vector& left);
	friend Vector operator+(const Vector& right, const double& left);
	friend Vector operator-(const Vector& right, const Vector& left);
	friend Vector operator-(const Vector& right, const double& left);

	Vector& operator=(const Vector& other);


	friend std::ostream& operator<<(std::ostream& cout, const Vector& vector);
	
};

#endif /* VECTOR_H */
