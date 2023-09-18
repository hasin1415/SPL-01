//
// Created by ASUS on 9/9/2023.
//
#ifndef SPL_01_MATRIXMANIPULATOR_H
#define SPL_01_MATRIXMANIPULATOR_H
#include "vector"
#include "CSVData.h"
#include "iostream"
class MatrixManiPulator {
    CSVData csvDataOne;
    CSVData csvDataTwo;
public:
    std::vector<std::vector<double>> CSVDataToMatrix(CSVData csvData) {
        std::vector<std::vector<double>> matrix;
        for (const std::vector<double> &row : csvData.data) {
            matrix.push_back(row);
        }
        return matrix;
    }
    std::vector<std::vector<double>> matrix_multiplication(std::vector<std::vector<double>> A,std:: vector<std::vector<double>> B) {
        // Check if the matrices can be multiplied.
        int m = A.size();
        int n = A[0].size();
        int p = B[0].size();
        if (n != B.size()) {
            std::cout << "invalid size";
        }

        std::vector<std::vector<double>> C(m, std::vector<double>(p));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < p; j++) {
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        return C;
    }
    std::vector<std::vector<double>> matrix_transpose(std::vector<std::vector<double>> A) {
        int m = A.size();
        int n = A[0].size();
        std::vector<std::vector<double>> T(n,std:: vector<double>(m));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                T[j][i] = A[i][j];
            }
        }

        return T;
    }
    void matrix_adder(std::vector<std::vector<int>> m1, std::vector<std::vector<int>> m2, std::vector<std::vector<int>> m3) {

        if (m1.size() != m2.size() || m1[0].size() != m2[0].size()) {
            std::cout << "The matrices must have the same dimensions." << std::endl;
            return;
        }
        for (int i = 0; i < m1.size(); i++) {
            for (int j = 0; j < m1[0].size(); j++) {
                m3[i][j] = m1[i][j] + m2[i][j];
            }
        }
    }
};
#endif //SPL_01_MATRIXMANIPULATOR_H
