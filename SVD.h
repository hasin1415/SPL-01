//
// Created by ASUS on 10/3/2023.
//

#ifndef SPL_01_SVD_H
#define SPL_01_SVD_H

#include "vector"
#include "cmath"
class SVD {
    void singularvaluedecomposition(std::vector<std::vector<double >> mat){
        int m = mat.size();
        int n = mat[0].size();
        std::vector<std::vector<double >> U(m,std::vector<double>(m));
        std::vector<std::vector<double >> V(n,std::vector<double>(n));
        std::vector<double> s(n);
        std::vector<double> e(n);
        std::vector<double> work(m);
        int wantu = 1;
        int wantv = 1;
        int i, j, k, l, l1, c, t;
        double g, scale, x, y, z, s1, s2, h;
        double *pU, *pV, *pS;
        double temp;

        // Copy A to U
        for (i = 0; i < m; i++)
            for (j = 0; j < n; j++)
                U[i][j] = mat[i][j];

        // Householder's reduction to bidiagonal form
        g = scale = x = 0.0;
        for (i = 0; i < n; i++) {
            e[i] = scale * g;
            s1 = s2 = scale = 0.0;
            for (k = i; k < m; k++)
                scale += fabs(U[k][i]);
            if (scale) {
                for (k = i; k < m; k++) {
                    U[k][i] /= scale;
                    s1 += U[k][i] * U[k][i];
                }
                f = U[i][i];
                g = -SIGN(sqrt(s1), f);
                h = f * g - s1;
                U[i][i] = f - g;
                for (j = l; j < n; j++) {
                    for (s2 = 0.0, k = i; k < m; k++)
                        s2 += U[k][i] * U[k][j];
                    f = s2 / h;
                    for (k = i; k < m; k++)
                        U[k][j] += f * U[k][i];
                }
                for (k = i; k < m; k++)
                    U[k][i] *= scale;
            }
            s[i] = scale * g;
            g = s1 = scale = 0.0

    }

};


#endif //SPL_01_SVD_H
