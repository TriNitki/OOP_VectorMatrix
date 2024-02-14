#pragma once
#include "Base.h"
#include "Vector.h"
class Matrix : public Base
{
public:
	Matrix(size_t size, double* values);

	Matrix(size_t rows = 0, size_t columns = 0, double* values = nullptr);

	Matrix(const Matrix& other);

	Matrix(Matrix&& other) noexcept;

	double getValue(size_t row, size_t column) const;

	void setValue(double value, size_t row, size_t column);

	Matrix& operator=(const Base& other);

	Matrix& operator=(Matrix&& other) noexcept;

	Matrix& operator+=(const Base& other);

	Matrix& operator-=(const Base& other);

	Matrix& operator*=(const Base& other);

	Matrix& operator*=(double scalar);

	Vector operator[](size_t index);

	Vector operator[](size_t index) const;
};

Matrix operator+(const Matrix& first, const Base& second);

Matrix operator-(const Matrix& first, const Base& second);

Matrix operator*(const Matrix& first, const Base& second);

Matrix operator*(const Matrix& matrix, double scalar);