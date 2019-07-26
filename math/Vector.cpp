
#include "Vector.h"

Vector::Vector(): m_length(0), m_elements(NULL) {}

Vector::Vector(int m_length): m_length(m_length)
{
	m_elements = new data_type[m_length];
}

Vector::Vector(int m_length, data_type value): Vector(m_length)
{
	std::fill(m_elements, m_elements + m_length, value);
}

Vector::Vector(const Vector& other): Vector(other.m_length)
{
	std::copy(other.m_elements, other.m_elements + m_length, m_elements);
}

Vector::Vector(std::vector<data_type> input): Vector(input.size())
{
	std::copy(input.begin(), input.end(), m_elements);
}

Vector::Vector(std::initializer_list<data_type> input): Vector(input.size())
{
	std::copy(input.begin(), input.end(), m_elements);
}

Vector::~Vector()
{
	delete [] m_elements;
}

void Vector::set_length(int length)
{
	if(m_length != length)
	{
		delete [] m_elements;
		m_length = length;
		m_elements = new data_type[m_length];
	}
}

Vector& Vector::map(data_type (*foo)(data_type))
{
	for (int i = 0; i < m_length; i++)
		set(i, foo(get(i)));
	return *this;
}

std::vector<data_type> Vector::to_std_vector() const 
{
	std::vector<data_type> result(m_length);
	std::copy(m_elements, m_elements + m_length, result.begin());
	return result;
}

Vector Vector::hamming_product(const Vector& right, const Vector& left)
{
	verify(right.m_length == left.m_length, 
		"Vectors must be the same length to calculate their hamming product!");

	Vector result(left.m_length);
	for (int i = 0; i < result.m_length; i++)
		result.set(i, left.get(i) * right.get(i));
	return result;
}

Vector operator*(const Vector& left, const data_type& right)
{
	Vector result(left.m_length);
	for (int i = 0; i < result.m_length; i++)
		result.set(i, left.get(i) * right);
	return result;
}

Vector operator*(const Matrix& left, const Vector& right)
{
	verify(left.m_cols == right.m_length, 
		"Invalid dimentions for Matrix and Vector multiplication!");

	Vector result(left.m_rows, 0);
	for (int r = 0; r < result.m_length; r++)
		for (int c = 0; c < right.m_length; c++)
			result.m_elements[r] += left.get(r, c) * right.get(c); //Change to set()
	return result;
}

Vector operator+(const Vector& left, const Vector& right)
{
	verify(left.m_length == right.m_length,
		"Invalid dimentions for vector addition!");

	Vector result(left.m_length);
	for (int i = 0; i < result.m_length; i++)
		result.set(i, left.get(i) + right.get(i));
	return result;
}

Vector operator-(const Vector& left, const Vector& right)
{
	verify(left.m_length == right.m_length,
		"Invalid dimentions for vector subtractions!");

	Vector result(left.m_length);
	for (int i = 0; i < result.m_length; i++)
		result.set(i, left.get(i) - right.get(i));
	return result;
}

Vector& Vector::operator=(const Vector& other)
{
	if(this != &other)
	{
		set_length(other.m_length);
		std::copy(other.m_elements, other.m_elements + m_length, m_elements);
	}
	return *this;
}

Vector& Vector::operator-=(const Vector& other)
{
	verify(m_length == other.m_length,
		"Invalid dimentions for vector subtractions!");
	
	for (int i = 0; i < m_length; i++) 
		m_elements[i] -= other.m_elements[i];
	return *this;
}


std::ostream& operator<<(std::ostream& cout, const Vector& vector)
{
	cout << "[";

	for (int i = 0; i < vector.m_length - 1; i++)
		cout << vector.get(i) << ", ";

	cout << vector.get(vector.m_length - 1) << "]\n";
	return cout;
}

std::ofstream& operator<<(std::ofstream& file, const Vector& vector)
{
	file.write((char*)(&vector.m_length), sizeof(unsigned int)/sizeof(char));
	file.write((char*)vector.m_elements, (sizeof(data_type)/sizeof(char)) * vector.m_length);
	return file;
}

std::ifstream& operator>>(std::ifstream& file, Vector& vector)
{
	int len = 0;
	file.read((char*)(&len), sizeof(unsigned int)/sizeof(char));
	vector.set_length(len);
	file.read((char*)vector.m_elements, (sizeof(data_type)/sizeof(char)) * vector.m_length);
	return file;
}
