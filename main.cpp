#include "matrix.hpp"

int main() 
{
    srand(time(nullptr));

    int m, n;
    std::cout << "Enter the value of m: ";
    std::cin >> m;
    std::cout << "Enter the value of n: ";
    std::cin >> n;

    Matrix<int> matrix(m, n);

    std::cout << "Original matrix:" << std::endl;
    matrix.print();

    // Writing matrix to a file
    std::ofstream outFile("matrix2222.txt");
    if (outFile.is_open()) 
    {
        outFile << m << " " << n << std::endl;  // Write dimensions first
        outFile << matrix;
        outFile.close();
        std::cout << "\nMatrix written to file 'matrix2222.txt'" << std::endl;
    } 
    else 
    {
        std::cerr << "Error: Unable to open file" << std::endl;
    }

    // Reading matrix from a file
    Matrix<int> fileMatrix("matrix2222.txt");
    std::cout << "\nMatrix read from file 'matrix2222.txt':" << std::endl;
    fileMatrix.print();

    // Reading two matrices from files
    Matrix<int> matrix1("matrix1.txt");
    Matrix<int> matrix2("matrix2.txt");

    std::cout << "\nMatrix1 read from file 'matrix1.txt':" << std::endl;
    matrix1.print();

    std::cout << "\nMatrix2 read from file 'matrix2.txt':" << std::endl;
    matrix2.print();

    Matrix<int> result = matrix1 * matrix2;
    std::cout << "\nResult of matrix1 * matrix2:" << std::endl;
    result.print();

    // Writing the result matrix to a file
    std::ofstream resultFile("result_matrix.txt");
    if (resultFile.is_open()) 
    {
        resultFile << result;
        resultFile.close();
        std::cout << "\nResult matrix written to file 'result_matrix.txt'" << std::endl;
    } 
    else 
    {
        std::cerr << "Error: Unable to open result file" << std::endl;
    }

    return 0;
}
