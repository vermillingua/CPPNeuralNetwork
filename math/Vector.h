
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <initializer_list>
#include <vector>

struct Matrix;

struct Vector
{
	friend Matrix;

private:
	int length;
	double* elements;

	void set_length(int length);

	inline double get(int pos) const {
		return elements[pos];
	}

	inline void set(int pos, double value) {
		elements[pos] = value;
	}

public:
	Vector();
	Vector(int length);
	Vector(int length, double value);
	Vector(const Vector& other);
	Vector(const std::vector<double> other);
	Vector(std::initializer_list<double> input);

	~Vector();

	Vector& map(double (*foo)(double));

	std::vector<double> to_std_vector() const;

	static Vector hamming_product(const Vector& right, const Vector& left);

	friend Vector operator+(const Vector& right, const Vector& left);
	friend Vector operator-(const Vector& right, const Vector& left);

	friend Vector operator*(const Vector& right, const double& left);
	friend Vector operator*(const Matrix& right, const Vector& left);

	friend Matrix outer_prod(const Vector& right, const Vector& left);

	Vector& operator=(const Vector& other);
	Vector& operator-=(const Vector& other);

	friend std::ostream& operator<<(std::ostream& cout, const Vector& vector);
	friend std::ofstream& operator<<(std::ofstream& file, const Vector& vector);
	friend std::ifstream& operator>>(std::ifstream& file, Vector& vector);
};

#endif /* VECTOR_H */
