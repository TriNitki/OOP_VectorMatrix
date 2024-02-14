#include "Vector.h"

Vector::Vector(const Vector& other) : 
	Base(other._rows, other._cols, other._data) {}

Vector::Vector(size_t size, double* values) :
    Base(1, size, values) {}

Vector::Vector(Vector&& other) noexcept :
    Base(std::move(other)) {};

double& Vector::operator[](size_t index)
{
    if (index >= _cols * _rows)
    {
        throw std::out_of_range("Index out of range. Object id: " + std::to_string(_id));
    }

    return _data[index];
}

double Vector::operator[](size_t index) const
{
    if (index >= _cols * _rows)
    {
        throw std::out_of_range("Index out of range. Object id: " + std::to_string(_id));
    }

    return _data[index];
}

Vector& Vector::operator=(const Base& other)
{
    if (_rows != other.getCols())
    {
        _rows = other.getCols();
        _data = new double[_rows];
    }

    for (int i = 0; i < _rows; i++)
    {
        _data[i] = other.getValue(i);
    }

    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    std::swap(this->_cols, other._cols);
    std::swap(this->_rows, other._rows);
    std::swap(this->_data, other._data);

    return *this;
}


Vector& Vector::operator+=(const Base& other)
{
    if (not canSum(*this, other))
    {
        throw std::invalid_argument(
            "Objects have different size. Object 1 id: " + std::to_string(_id) + ", Object 2 id: " + 
            std::to_string(other.getId()));
    }

    size_t size = _cols;

    for (int i = 0; i < size; i++)
    {
        _data[i] = _data[i] + other.getValue(i);
    }

    return *this;
}

Vector& Vector::operator-=(const Base& other)
{
    if (not canSum(*this, other))
    {
        throw std::invalid_argument(
            "Objects have different size. Object 1 id: " + std::to_string(_id) + ", Object 2 id: " + 
            std::to_string(other.getId()));
    }

    size_t size = _cols;

    for (int i = 0; i < size; i++)
    {
        _data[i] = _data[i] - other.getValue(i);
    }

    return *this;
}

Vector& Vector::operator*=(double scalar)
{
    size_t size = _cols;

    for (int i = 0; i < size; i++)
    {
        _data[i] = _data[i] * scalar;
    }
    return *this;
}

Vector operator+(const Vector& first, const Base& second)
{
    Vector sum = first;
    sum += second;
    return sum;
}

Vector operator-(const Vector& first, const Base& second)
{
    Vector dif = first;
    dif -= second;
    return dif;
}

Vector operator*(const Vector& vector, double scalar)
{
    Vector mul = vector;
    mul *= scalar;
    return mul;
}

double operator*(const Vector& first, const Base& second)
{
    if (not canSum(first, second))
    {
        throw std::invalid_argument(
            "Objects have different size. Object 1 id: " + std::to_string(first.getId()) + ", Object 2 id: " + 
            std::to_string(second.getId()));
    }

    size_t size = first.getCols();
    double result = 0;

    for (int i = 0; i < size; i++)
    {
        result += first[i] * second.getValue(i);
    }

    return result;
}