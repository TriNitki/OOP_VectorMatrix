#include "Base.h"

unsigned int idCounter = 1;

// Base

Base::Base(size_t rows, size_t cols, double* values)
{
    _rows = rows;
    _cols = cols;

    _data = new double[_rows * _cols];

    if (values != nullptr)
    {
        for (int i = 0; i < _rows * _cols; i++)
        {
            _data[i] = values[i];
        }
    }

    _id = idCounter++;
}

Base::Base(const Base& other):
    Base(other._rows, other._cols, other._data) {}

Base::Base(Base&& other) noexcept
{
    std::swap(this->_cols, other._cols);
    std::swap(this->_rows, other._rows);
    std::swap(this->_data, other._data);

    _id = idCounter++;
}

Base::~Base()
{
    if (_data != nullptr)
    {
        delete[] _data;
    }
}

int Base::getRows() const
{
    return (int)_rows;
}

int Base::getCols() const
{
    return (int)_cols;
}

double* Base::getData() const
{
    return _data;
}

int Base::getId() const
{
    return _id;
}

double Base::getValue(size_t index) const
{
    if (_rows * _cols <= index)
    {
        throw std::out_of_range("Index out of range. Object id: " + std::to_string(_id));
    }

    return _data[index];
}

bool Base::canSum(const Base& other) const
{
    return getRows() == other.getRows() && getCols() == other.getCols();
}

bool Base::canMul(const Base& other) const
{
    return getRows() == other.getCols();
}

void Base::setRows(size_t newRows)
{
    _rows = newRows;
}

void Base::setCols(size_t newCols)
{
    _cols = newCols;
}

void Base::setValue(double value, size_t index)
{
    if (_rows * _cols <= index)
    {
        throw std::out_of_range("Index out of range. Object id: " + std::to_string(_id));
    }

    _data[index] = value;
}

Base& Base::operator=(Base&& other) noexcept
{
    std::swap(this->_cols, other._cols);
    std::swap(this->_rows, other._rows);
    std::swap(this->_data, other._data);

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Base& base)
{
    int rows = (int)base.getRows();
    int cols = (int)base.getCols();

    os << "Object Id." << base.getId() << ":" << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            os << std::setw(4) << std::setprecision(4) << base.getValue(i * cols + j) << " ";
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Base& base)
{
    double value;
    int rows = (int)base.getRows();
    int cols = (int)base.getCols();
    for (int i = 0; i < rows * cols; i++)
    {
        is >> value;
        base.setValue(value, i);
    }
    return is;
}

// Vector

Vector::Vector(const Vector& other) :
    Base(other) {}

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

Base& Vector::operator=(const Base& other)
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

Base& Vector::operator+=(const Base& other)
{
    if (!canSum(other))
    {
        throw std::invalid_argument(
            "Objects have different size. Object 1 id: " + std::to_string(_id) + 
            ", Object 2 id: " + std::to_string(other.getId()));
    }

    size_t size = _cols;

    for (int i = 0; i < size; i++)
    {
        _data[i] = _data[i] + other.getValue(i);
    }

    return *this;
}

Base& Vector::operator-=(const Base& other)
{
    if (!canSum(other))
    {
        throw std::invalid_argument(
            "Objects have different size. Object 1 id: " + std::to_string(_id) + 
            ", Object 2 id: " + std::to_string(other.getId()));
    }

    size_t size = _cols;

    for (int i = 0; i < size; i++)
    {
        _data[i] = _data[i] - other.getValue(i);
    }

    return *this;
}

Base& Vector::operator*=(double scalar)
{
    size_t size = _cols;

    for (int i = 0; i < size; i++)
    {
        _data[i] = _data[i] * scalar;
    }
    return *this;
}

// Matrix

Matrix::Matrix(size_t otherSize, double* values) :
    Base(otherSize, otherSize, values) {}

Matrix::Matrix(size_t rows, size_t columns, double* values) :
    Base(rows, columns, values) {}

Matrix::Matrix(const Matrix& other) :
    Base(other) {}

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

Base& Matrix::operator+=(const Base& other)
{
    if (!canSum(other))
    {
        throw std::invalid_argument(
            "Objects have different dimensions. Object 1 id: " + std::to_string(_id) + 
            ", Object 2 id: " + std::to_string(other.getId()));
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

Base& Matrix::operator-=(const Base& other)
{
    if (!canSum(other))
    {
        throw std::invalid_argument(
            "Objects have different dimensions. Object 1 id: " + std::to_string(_id) + 
            ", Object 2 id: " + std::to_string(other.getId()));
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

Base& Matrix::operator*=(double scalar)
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

Base& Matrix::operator=(const Base& other)
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

Matrix& Matrix::operator*=(const Base& other)
{
    if (!canMul(other))
    {
        throw std::invalid_argument(
            "Columns of the first object must be equal to rows of the second object. Object 1 id: " +
            std::to_string(_id) + ", Object 2 id: " + std::to_string(other.getId()));
    }

    int rows = getRows();
    int columns = other.getCols();
    double sum;

    setRows(rows);
    setCols(columns);

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

// Operators

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
    if (first.canMul(second))
    {
        throw std::invalid_argument(
            "Objects have different size. Object 1 id: " + 
            std::to_string(first.getId()) + ", Object 2 id: " +
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
