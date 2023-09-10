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
};


#endif //SPL_01_MATRIXMANIPULATOR_H
