#include <iostream>
#include <cstdlib>
#include <ctime>

class Matrix 
{
private:
    int** data;
    int rows;
    int cols;

public:
    Matrix(int m, int n) : rows(m), cols(n) 
    {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) 
        {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j) 
            {
                data[i][j] = rand() % 100 + 1;
            }
        }
    }

    ~Matrix() 
    {
        for (int i = 0; i < rows; ++i) 
        {
            delete[] data[i];
        }
        delete[] data;
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) 
    {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) 
        {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j) 
            {
                data[i][j] = other.data[i][j];
            }
        }
    }


    Matrix& operator++() 
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

    Matrix operator++(int) 
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

    Matrix operator+(const Matrix& other) const 
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

    Matrix& operator=(const Matrix& other) 
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

            data = new int*[rows];
            for (int i = 0; i < rows; ++i) 
            {
                data[i] = new int[cols];
                for (int j = 0; j < cols; ++j) 
                {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }


    void print() const 
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

    Matrix transpose() const 
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
};

int main() 
{
    srand(time(nullptr));

    int m, n;
    std::cout << "Enter the value of m: ";
    std::cin >> m;
    std::cout << "Enter the value of n: ";
    std::cin >> n;

    Matrix matrix(m, n);

    std::cout << "Original matrix:" << std::endl;
    matrix.print();

    ++matrix;
    std::cout << "\nAfter prefix increment:" << std::endl;
    matrix.print();

    matrix++; 
    std::cout << "\nAfter postfix increment:" << std::endl;
    matrix.print();

    return 0;
}
