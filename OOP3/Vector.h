#pragma once
#include "Base.h"
class Vector : public Base 
{
public:
    Vector(size_t size = 0, double* values = nullptr);

    Vector(Vector&& other) noexcept;

	Vector(const Vector& other);

    Vector& operator=(const Base& other);

    Vector& operator=(Vector&& other) noexcept;

    Vector& operator+=(const Base& other);

    Vector& operator-=(const Base& other);

    Vector& operator*=(double scalar);

    double& operator[](size_t index);

    double operator[](size_t index) const;
};

Vector operator+(const Vector& first, const Base& second);

Vector operator-(const Vector& first, const Base& second);

double operator*(const Vector& first, const Base& second);

Vector operator*(const Vector& vector, double scalar);
