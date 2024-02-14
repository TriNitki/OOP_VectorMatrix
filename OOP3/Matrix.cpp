#include "Matrix.h"

Matrix::Matrix(size_t otherSize, double* values) :
	Base(otherSize, otherSize, values) {}

Matrix::Matrix(size_t rows, size_t columns, double* values) :
	Base(rows, columns, values) {}

Matrix::Matrix(const Matrix& other) :
	Base(other._rows, other._cols, other._data) {}

Matrix::Matrix(Matrix&& other) noexcept :
    Base(std::move(other)) {};

double Matrix::getValue(size_t row, size_t column) const 
{
    if (row > this->_rows || column > this->_cols)
    {
        throw std::out_of_range("Index out of range. Object id: " + std::to_string(_id));
    }

    return _data[row * _cols + column];
}

void Matrix::setValue(double value, size_t row, size_t column)
{
	if (row > this->_rows || column > this->_cols)
	{
        throw std::out_of_range("Index out of range. Object id: " + std::to_string(_id));
	}

	_data[row * _cols + column] = value;
}

Vector Matrix::operator[](size_t index)
{
    if (index >= _rows)
    {
        throw std::out_of_range("Index out of range. Object id: " + std::to_string(_id));
    }
    double* newData = new double[_cols];

    for (size_t i = _cols * index; i < _cols * (index + 1); i++)
    {
        newData[i % _cols] = _data[i];
    }

    return Vector(_cols, newData);;
}

Vector Matrix::operator[](size_t index) const {
    if (index >= _rows)
    {
        throw std::out_of_range("Index out of range. Object id: " + std::to_string(_id));
    }
    double* newData = new double[_cols];

    for (size_t i = _cols * index; i < _cols * (index + 1); i++)
    {
        newData[i % _cols] = _data[i];
    }

    Vector newVector(_cols, newData);
    return newVector;
}

Matrix& Matrix::operator+=(const Base& other)
{
    if (not canSum(*this, other))
    {
        throw std::invalid_argument(
            "Objects have different dimensions. Object 1 id: " + std::to_string(_id) + ", Object 2 id: " + 
            std::to_string(other.getId()));
    }

    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            setValue(getValue(i, j) + other.getValue(i * _cols + j), i, j);
        }
    }

    return *this;
}

Matrix& Matrix::operator-=(const Base& other)
{
    if (not canSum(*this, other))
    {
        throw std::invalid_argument(
            "Objects have different dimensions. Object 1 id: " + std::to_string(_id) + ", Object 2 id: " + 
            std::to_string(other.getId()));
    }
      

    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            setValue(getValue(i, j) - other.getValue(i * _cols + j), i, j);
        }
    }

    return *this;
}

Matrix& Matrix::operator*=(double scalar)
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            setValue(getValue(i, j) * scalar, i, j);
        }
    }

    return *this;
}

Matrix& Matrix::operator=(const Base& other)
{
    if (this == &other)
    {
        return *this;
    }

    if (_rows * _cols != other.getRows() * other.getCols())
    {
        _rows = other.getRows();
        _cols = other.getCols();
        _data = new double[_rows * _cols];
    }

    for (int i = 0; i < _rows * _cols; i++)
    {
        _data[i] = other.getValue(i);
    }

    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
    std::swap(this->_cols, other._cols);
    std::swap(this->_rows, other._rows);
    std::swap(this->_data, other._data);

    return *this;
}

Matrix& Matrix::operator*=(const Base& other)
{
    if (not canMul(*this, other))
    {
        throw std::invalid_argument(
            "Columns of the first object must be equal to rows of the second object. Object 1 id: " + 
            std::to_string(_id) + "Object 2 id: " + std::to_string(other.getId()));
    }

    int rows = getRows();
    int columns = other.getCols();
    double sum;

    double* resultData = new double[rows * columns];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            sum = 0.0;
            for (int k = 0; k < columns; k++)
                sum += getValue(i, k) * other.getValue(k * _cols + j);
            resultData[i * columns + j] = sum;
        }
    }

    _data = resultData;
    return *this;
}

Matrix operator+(const Matrix& first, const Base& second)
{
    Matrix sum = first;
    sum += second;
    return sum;
}

Matrix operator-(const Matrix& first, const Base& second)
{
    Matrix dif = first;
    dif -= second;
    return dif;
}

Matrix operator*(const Matrix& first, const Base& second)
{
    Matrix mul = first;
    mul *= second;
    return mul;
}

Matrix operator*(const Matrix& matrix, double scalar)
{
    Matrix mul = matrix;
    mul *= scalar;
    return mul;
}