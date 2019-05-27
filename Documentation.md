# Matrix Math Library
## Private
- int rows
- int cols
- double* elements


- int size() const

- void set(int row, int col, double value)
- double get(int row, int col) const
- void setDimensions(int rows, int cols)

## Public
- Matrix()
- Matrix(int rows, int cols)
- Matrix(int rows, int cols, double value)
- Matrix(std:initializer_list<std::initializer_list<double> > input)
- static Matrix identity(int dimension)
- ~Matrix()
- double trace() const
- Matrix transpose() const
- void map(double (*foo)(double))
- Matrix& operator=(const Matrix& other)
- Matrix& operator*=(const Matrix& other)
- Matrix& operator*=(const int& other)
- Matrix& operator+=(const Matrix& other)
- Matrix& operator+=(const int& other)
- Matrix& operator-=(const Matrix& other)
- Matrix& operator-=(const int& other)


## Friend
- Matrix operator*(const Matrix& left, const Matix& right)
- Matrix operator*(const Matrix& left, const int& right)
- Matrix operator+(const Matrix& left, const Matix& right)
- Matrix operator+(const Matrix& left, const int& right)
- Matrix operator-(const Matrix& left, const Matix& right)
- Matrix operator-(const Matrix& left, const int& right)
- Matrix operator^(const Matrix& left, const int& right)
