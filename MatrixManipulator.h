//
// Created by ASUS on 12/16/2023.
//

#ifndef SPL_01_MATRIXMANIPULATOR_H
#define SPL_01_MATRIXMANIPULATOR_H
#include <iostream>
#include <vector>
#include <cmath>

class MatrixManipulator {
public:
    std::vector<std::vector<long double>> matrixMultiplicator(const std::vector<std::vector<long double>>& matrixOne, const std::vector<std::vector<long double>>& matrixTwo) {
        int m = matrixOne.size();
        int n = matrixTwo[0].size();
        int p = matrixTwo.size();
        std::vector<std::vector<long double>> result(m, std::vector<long double>(n, 0.0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < p; ++k) {
                    result[i][j] += matrixOne[i][k] * matrixTwo[k][j];
                }
            }
        }
        return result;
    }

    // Function to perform dot product of matrix and vector
    std::vector<long double> matrixDotProduct(const std::vector<std::vector<long double>>& matrix, const std::vector<long double>& Vector) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        std::vector<long double> result(rows, 0.0);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[i] += matrix[i][j] * Vector[j];
            }
        }
        return result;
    }
    std::vector<std::vector<long double>> matrixTransposeProduct(const std::vector<std::vector<long double>>& matrix) {
        std::vector<std::vector<long double>> transpose = matrixTranspose(matrix);
        return matrixMultiplicator(matrix, transpose);
    }
    std::vector<std::vector<long double>> matrixTranspose(const std::vector<std::vector<long double>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        std::vector<std::vector<long double>> transpose(cols, std::vector<long double>(rows, 0.0));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                transpose[j][i] = matrix[i][j];
            }
        }
        return transpose;
    }
    // Function to calculate mean of a vector
    long double meanVector(const std::vector<long double>& Vector) {
        long double sum = 0.0;
        for (long double val : Vector) {
            sum += val;
        }
        return sum / Vector.size();
    }
    // Function to calculate standard deviation of a vector
    long double standardDeviationVector(const std::vector<long double>& Vector) {
        long double mean = meanVector(Vector);
        long double variance = 0.0;

        for (long double val : Vector) {
            variance += (val - mean) * (val - mean);
        }

        variance /= Vector.size();
        return sqrt(variance);
    }
    std::vector<long double> vectorSubtraction(const std::vector<long double>& VectorOne, const std::vector<long double>& VectorTwo) {
        int size = VectorOne.size();
        std::vector<long double> result(size, 0.0);
        for (int i = 0; i < size; ++i) {
            result[i] = VectorOne[i] - VectorTwo[i];
        }
        return result;
    }
    long double vectorDotProduct(const std::vector<long double>& VectorOne, const std::vector<long double>& VectorTwo) {
        int size = VectorOne.size();
        long double result = 0.0;
        for (int i = 0; i < size; ++i) {
            result += VectorOne[i] * VectorTwo[i];
        }
        return result;
    }
    std::vector<long double> scalarMultiplication(const long double& scalar, const std::vector<long double>& Vector) {
        int size = Vector.size();
        std::vector<long double> result(size, 0.0);
        for (int i = 0; i < size; ++i) {
            result[i] = scalar * Vector[i];
        }
        return result;
    }

};


#endif //SPL_01_MATRIXMANIPULATOR_H
