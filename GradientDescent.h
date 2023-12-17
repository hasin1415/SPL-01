//
// Created by ASUS on 12/13/2023.
//

#ifndef SPL_01_GRADIENTDESCENT_H
#define SPL_01_GRADIENTDESCENT_H
#include "CSVReader.h"
#include "MatrixManipulator.h"


class GradientDescent {
private:
    std::string filePath;
    int numRows;
    std::vector<long double> coefficients;
    CSVReader reader;
public:
    GradientDescent(const std::string &path, CSVReader reader) : filePath(path), numRows(0), reader(reader) {
        coefficients = ComputeGradientDescent();
    }
    std::vector <long double> get_coefficients() {
        return coefficients;
    }
    std::vector<long double> ComputeGradientDescent() {
        std::vector<long double> x_one = reader.getColumn("Distance (LY)");
        std::vector<long double> x_two = reader.getColumn("Temperature (K)");
        std::vector<long double> y = reader.getColumn("Brightness");
        int NumberRows = reader.getNumberRows();
        MatrixManipulator matrixManipulator;
        long double x_one_mean = matrixManipulator.meanVector(x_one);
        long double x_two_mean = matrixManipulator.meanVector(x_two);
        long double x_one_variance = matrixManipulator.standardDeviationVector(x_one);
        long double x_two_variance = matrixManipulator.standardDeviationVector(x_two);
        for (int i = 0; i < NumberRows; i++) {
            x_one[i] = (x_one[i] - x_one_mean) / x_one_variance;
            x_two[i] = (x_two[i] - x_two_mean) / x_two_variance;
        }
        std::vector<long double> ones(NumberRows, 1.0);
        std::vector<std::vector<long double>> matrix;
        matrix.push_back(x_one);
        matrix.push_back(x_two);
        matrix.push_back(ones);
        matrix = matrixManipulator.matrixTranspose(matrix);
        long double learning_rate = 0.01;
        int epochs = 2000;
        int N = y.size();
        std::vector<long double> coeff = {0.696469, 0.286139, 0.226851};
        std::vector<long double> prediction;
        std::vector<long double> error;
        std::vector<long double> der;
        std::vector<long double> past_costs;
        while (epochs--) {
            //  std::cout << "Epochs: " << epochs << std::endl;
            prediction = matrixManipulator.matrixDotProduct(matrix, coeff);
            error = matrixManipulator.vectorSubtraction(prediction, y);
            long double tempOne = matrixManipulator.vectorDotProduct(error, error);
            long double cost = (1.0 / (2.0 * (long double) N)) * tempOne;
            past_costs.push_back(cost);
            std::vector<long double> tempTwo = matrixManipulator.matrixDotProduct(
                    matrixManipulator.matrixTranspose(matrix), error);
            der = matrixManipulator.scalarMultiplication((1.0 /(long double ) N) * learning_rate, tempTwo);
            //std::cout << "finished"<<std::endl;
            coeff = matrixManipulator.vectorSubtraction(coeff, der);
            //  std::cout << "Coefficients: " << coeff[0] << " " << coeff[1] << " " << coeff[2] << std::endl;
        }
        return coeff;
    }
    const std::string &getFilePath() const {
        return filePath;
    }

    void setFilePath(const std::string &filePath) {
        GradientDescent::filePath = filePath;
    }
    int getNumRows() const {
        return numRows;
    }
    void setNumRows(int numRows) {
        GradientDescent::numRows = numRows;
    }
    const std::vector<long double> &getCoefficients() const {
        return coefficients;
    }
    void setCoefficients(const std::vector<long double> &coefficients) {
        GradientDescent::coefficients = coefficients;
    }
    const CSVReader &getReader() const
    {
        return reader;
    }
    void setReader(const CSVReader &reader)
    {
        GradientDescent::reader = reader;
    }
    long double predictBrightness(long double area, long double basement, std::vector<long double> coefficients)
    {
        MatrixManipulator matrixManipulator;
        std::vector<long double> x_one = reader.getColumn("GrLivArea");
        std::vector<long double> x_two = reader.getColumn("Temperature (K)");
        long double x_one_mean = matrixManipulator.meanVector(x_one);
        long double x_two_mean = matrixManipulator.meanVector(x_two);
        long double x_one_variance = matrixManipulator.standardDeviationVector(x_one);
        long double x_two_variance = matrixManipulator.standardDeviationVector(x_two);
        area = (area - x_one_mean) / x_one_variance;
        basement = (basement - x_two_mean) / x_two_variance;
        long double predicted_price = coefficients[0] * area + coefficients[1] * basement + coefficients[2];
        return predicted_price;
    }
    long double predictBrightness(long double area, long double basement)
    {
        std::vector<long double> coefficient = get_coefficients();
        MatrixManipulator matrixManipulator;
        std::vector<long double> x_one = reader.getColumn("Distance (LY)");
        std::vector<long double> x_two = reader.getColumn("Temperature (K)");
        long double x_one_mean = matrixManipulator.meanVector(x_one);
        long double x_two_mean = matrixManipulator.meanVector(x_two);
        long double x_one_variance = matrixManipulator.standardDeviationVector(x_one);
        long double x_two_variance = matrixManipulator.standardDeviationVector(x_two);
        area = (area - x_one_mean) / x_one_variance;
        basement = (basement - x_two_mean) / x_two_variance;
        long double predicted_price = coefficients[0] * area + coefficients[1] * basement + coefficients[2];
        return predicted_price;
    }
};

#endif //SPL_01_GRADIENTDESCENT_H
