
#include "iostream"
#include "Gradient.h"
void gradientDescent(int maxIterations, double learningRate, double tolerance, double initialTheta0, double initialTheta1, vector<double> x, vector<double> y){
    int m = x.size();
    double theta0 = initialTheta0, theta1 = initialTheta1;
    double cost, cost1, cost2, temp0, temp1;
    for(int i = 0; i < maxIterations; i++){
        cost1 = 0, cost2 = 0;
        for(int j = 0; j < m; j++){
            cost1 += (theta0 + theta1 * x[j] - y[j]);
            cost2 += (theta0 + theta1 * x[j] - y[j]) * x[j];
        }
        temp0 = theta0 - (learningRate * cost1) / m;
        temp1 = theta1 - (learningRate * cost2) / m;
        theta0 = temp0, theta1 = temp1;
        cost = 0;
        for(int j = 0; j < m; j++){
            cost += pow(theta0 + theta1 * x[j] - y[j], 2);
        }
        cost /= (2 * m);
        if(cost < tolerance){
            break;
        }
    }
    cout << "theta0: " << theta0 << endl;
    cout << "theta1: " << theta1 << endl;

}