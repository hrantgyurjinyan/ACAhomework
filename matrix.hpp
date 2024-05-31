#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

template <typename T>
class Matrix 
{
private:
    T** data;
    int rows;
    int cols;

public:
    Matrix(int m, int n);
    Matrix(const std::string& filename);
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);
    Matrix& operator++();
    Matrix operator++(int);
    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    void print() const;
    Matrix transpose() const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix);
    
    template <typename U>
    friend std::istream& operator>>(std::istream& is, Matrix<U>& matrix);
};

// Constructor that initializes a matrix with random values
template <typename T>
Matrix<T>::Matrix(int m, int n) : rows(m), cols(n) 
{
    data = new T*[rows];
    for (int i = 0; i < rows; ++i) 
    {
        data[i] = new T[cols];
        for (int j = 0; j < cols; ++j) 
        {
            data[i][j] = static_cast<T>(rand() % 100 + 1);
        }
    }
}

// Constructor that initializes a matrix from a file
template <typename T>
Matrix<T>::Matrix(const std::string& filename) 
{
    std::ifstream inFile(filename);
    if (!inFile) 
    {
        std::cerr << "Error: Unable to open file" << std::endl;
        exit(1);
    }

    inFile >> rows >> cols;
    data = new T*[rows];
    for (int i = 0; i < rows; ++i) 
    {
        data[i] = new T[cols];
        for (int j = 0; j < cols; ++j) 
        {
            inFile >> data[i][j];
        }
    }
}

// Destructor
template <typename T>
Matrix<T>::~Matrix() 
{
    for (int i = 0; i < rows; ++i) 
    {
        delete[] data[i];
    }
    delete[] data;
}

// Copy constructor
template <typename T>
Matrix<T>::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) 
{
    data = new T*[rows];
    for (int i = 0; i < rows; ++i) 
    {
        data[i] = new T[cols];
        for (int j = 0; j < cols; ++j) 
        {
            data[i][j] = other.data[i][j];
        }
    }
}

// Move constructor
template <typename T>
Matrix<T>::Matrix(Matrix&& other) : data(nullptr), rows(0), cols(0)
{
    data = other.data;
    rows = other.rows;
    cols = other.cols;

    other.data = nullptr;
    other.rows = 0;
    other.cols = 0;
}

// Copy assignment operator
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) 
{
    if (this != &other) 
    {
        for (int i = 0; i < rows; ++i) 
        {
            delete[] data[i];
        }
        delete[] data;

        rows = other.rows;
        cols = other.cols;

        data = new T*[rows];
        for (int i = 0; i < rows; ++i) 
        {
            data[i] = new T[cols];
            for (int j = 0; j < cols; ++j) 
            {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

// Move assignment operator
template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) 
{
    if (this != &other) 
    {
        for (int i = 0; i < rows; ++i) 
        {
            delete[] data[i];
        }
        delete[] data;

        data = other.data;
        rows = other.rows;
        cols = other.cols;

        other.data = nullptr;
        other.rows = 0;
        other.cols = 0;
    }
    return *this;
}

// Increment operators
template <typename T>
Matrix<T>& Matrix<T>::operator++() 
{
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            data[i][j] += 3;
        }
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator++(int) 
{
    Matrix tmp = *this;
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            data[i][j] += 3;
        }
    }
    return tmp; 
}

// Addition operator
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const 
{
    if (rows != other.rows || cols != other.cols) 
    {
        std::cerr << "Error: Matrices have different dimensions. Addition not possible." << std::endl;
        exit(1); 
    }

    Matrix result(rows, cols);

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }

    return result;
}

// Multiplication operator
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const 
{
    if (cols != other.rows) 
    {
        std::cerr << "Error: Matrices have incompatible dimensions. Multiplication not possible." << std::endl;
        exit(1); 
    }

    Matrix result(rows, other.cols);

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < other.cols; ++j) 
        {
            result.data[i][j] = 0;
            for (int k = 0; k < cols; ++k) 
            {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }

    return result;
}

// Print the matrix
template <typename T>
void Matrix<T>::print() const 
{
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Transpose the matrix
template <typename T>
Matrix<T> Matrix<T>::transpose() const 
{
    Matrix transposed(cols, rows);
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            transposed.data[j][i] = data[i][j];
        }
    }
    return transposed;
}

// Overload the stream insertion operator
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) 
{
    for (int i = 0; i < matrix.rows; ++i) 
    {
        for (int j = 0; j < matrix.cols; ++j) 
        {
            os << matrix.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

// Overload the stream extraction operator
template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& matrix) 
{
    for (int i = 0; i < matrix.rows; ++i) 
    {
        for (int j = 0; j < matrix.cols; ++j) 
        {
            is >> matrix.data[i][j];
        }
    }
    return is;
}

