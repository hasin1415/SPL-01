//
// Created by ASUS on 9/9/2023.
//

#ifndef SPL_01_MATRIXMANIPULATOR_H
#define SPL_01_MATRIXMANIPULATOR_H

#include "vector"
class MatrixManiPulator {
    vector<vector<double>> matrix_multiplication(vector<vector<double>> A, vector<vector<double>> B) {
        // Check if the matrices can be multiplied.
        int m = A.size();
        int n = A[0].size();
        int p = B[0].size();
        if (n != B.size()) {
            cout << "invalid size";
        }

        vector<vector<double>> C(m, vector<double>(p));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < p; j++) {
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        return C;
    }
    vector<vector<double>> matrix_transpose(vector<vector<double>> A) {
        int m = A.size();
        int n = A[0].size();
        vector<vector<double>> T(n, vector<double>(m));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                T[j][i] = A[i][j];
            }
        }

        return T;
    }
    void matrix_adder(vector<vector<int>> m1, vector<vector<int>> m2, vector<vector<int>> m3) {
        // Check if the matrices have the same dimensions
        if (m1.size() != m2.size() || m1[0].size() != m2[0].size()) {
            cout << "The matrices must have the same dimensions." << endl;
            return;
        }

        // Add the matrices
        for (int i = 0; i < m1.size(); i++) {
            for (int j = 0; j < m1[0].size(); j++) {
                m3[i][j] = m1[i][j] + m2[i][j];
            }
        }
    }
};


#endif //SPL_01_MATRIXMANIPULATOR_H
