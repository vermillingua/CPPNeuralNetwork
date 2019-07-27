
#ifndef VECTOR_H
#define VECTOR_H

#include "LinearAlgebra.h"

#include <fstream>
#include <initializer_list>
#include <vector>

struct Matrix;

struct Vector
{
	friend Matrix;

private:
	int m_length;
	data_type* m_elements;

	inline data_type& get(int pos) const 
	{
		return m_elements[pos];
	}

	inline void set(int pos, data_type value) 
	{
		m_elements[pos] = value;
	}

	void set_length(int length);

public:
	Vector();
	Vector(int length);
	Vector(int length, data_type value);
	Vector(const Vector& other);
	Vector(const std::vector<data_type> other);
	Vector(std::initializer_list<data_type> input);

	~Vector();

	Vector& map(data_type (*foo)(data_type));

	int max_index() const;

	std::vector<data_type> to_std_vector() const;

	static Vector hamming_product(const Vector& right, const Vector& left);

	data_type& operator[](int index);

	friend Vector operator+(const Vector& right, const Vector& left);
	friend Vector operator-(const Vector& right, const Vector& left);

	friend Vector operator*(const Vector& right, const data_type& left);
	friend Vector operator*(const Matrix& right, const Vector& left);

	friend Matrix outer_prod(const Vector& right, const Vector& left);

	Vector& operator=(const Vector& other);
	Vector& operator-=(const Vector& other);

	friend std::ostream& operator<<(std::ostream& cout, const Vector& vector);
	friend std::ofstream& operator<<(std::ofstream& file, const Vector& vector);
	friend std::ifstream& operator>>(std::ifstream& file, Vector& vector);
};

#endif /* VECTOR_H */
