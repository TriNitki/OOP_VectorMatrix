#pragma once
#include <iostream>
#include <iomanip>
#include <string>

class Base
{
protected:
	double* _data;
	size_t _rows;
	size_t _cols;
	unsigned int _id;

	Base(size_t rows = 0, size_t columns = 0, const double* values = nullptr);

	Base(const Base& other);

	Base(Base&& other) noexcept;

	~Base();

public:
	int getRows() const;

	int getCols() const;

	double* getData() const;

	virtual double getValue(size_t index) const;

	int getId() const;

	void setRows(size_t newRows);

	void setCols(size_t newCols);

	Base& operator=(Base&& other) noexcept;

	virtual Base& operator=(const Base& other) = 0;

	virtual Base& operator+=(const Base& other) = 0;

	virtual Base& operator-=(const Base& other) = 0;

	virtual Base& operator*=(double scalar) = 0;

	virtual void setValue(double value, size_t index);

	bool canMul(const Base& other) const;

	bool canSum(const Base& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Base& base);

	friend std::istream& operator>>(std::istream& is, Base& base);
};

class Vector : public Base
{
public:
	Vector(size_t size = 0, const double* values = nullptr);

	Vector(Vector&& other) noexcept;

	Vector(const Vector& other);

	Base& operator=(const Base& other);

	Base& operator+=(const Base& other);

	Base& operator-=(const Base& other);

	Base& operator*=(double scalar);

	double& operator[](size_t index);

	double operator[](size_t index) const;
};

class Matrix : public Base
{
private:
	class Row {
	private:
		double* _data;
		size_t _size;
	public:
		Row(size_t size, double* values) :
			_data(values), _size(size) {}

		double& operator[](size_t col);

		double operator[](size_t col) const;
	};
public:
	Matrix(size_t size, const double* values);

	Matrix(size_t rows = 0, size_t columns = 0, const double* values = nullptr);

	Matrix(const Matrix& other);

	Matrix(Matrix&& other) noexcept;

	double getValue(size_t row, size_t column) const;

	void setValue(double value, size_t row, size_t column);

	Base& operator=(const Base& other);

	Base& operator+=(const Base& other);

	Base& operator-=(const Base& other);

	Matrix& operator*=(const Base& other);

	Base& operator*=(double scalar);

	Row operator[](size_t index);

	Row operator[](size_t index) const;
};

Matrix operator+(const Matrix& first, const Base& second);

Matrix operator-(const Matrix& first, const Base& second);

Matrix operator*(const Matrix& first, const Base& second);

Matrix operator*(const Matrix& matrix, double scalar);


Vector operator+(const Vector& first, const Base& second);

Vector operator-(const Vector& first, const Base& second);

double operator*(const Vector& first, const Base& second);

Vector operator*(const Vector& vector, double scalar);