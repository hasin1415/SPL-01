//
// Created by ASUS on 12/13/2023.
//

#ifndef SPL_01_CROSSVALIDATION_H
#define SPL_01_CROSSVALIDATION_H


#include "bits/stdc++.h"
#include "CSVReader.h"
#include "MatrixManipulator.h"
#include "GradientDescent.h"

class crossValidation {
private:
    std::vector<std::string> filenames;
    std::string filePath;
    int numRows;
    std::vector<long double> coefficients;
    CSVReader reader;
public:
    crossValidation(const std::string &path, CSVReader reader) : filePath(path), numRows(0), reader(reader) {
        reader.csvSplitter();
        filenames.push_back("split_1.csv");
        filenames.push_back("split_2.csv");
        filenames.push_back("split_3.csv");
        filenames.push_back("split_4.csv");
        CSVReader reader1(filenames[0]);
        //    GradientDescent testOne(filenames[0], reader1);
        CSVReader reader2(filenames[1]);
        //    GradientDescent testTwo(filenames[1], reader2);
        CSVReader reader3(filenames[2]);
        //      GradientDescent testThree(filenames[2], reader3);
        CSVReader reader4(filenames[3]);
        //   GradientDescent testFour(filenames[3], reader4);
        long double crossValidationRatio = 0.00;
        std::vector<std::string> listOne = {"split_1.csv", "split_2.csv", "split_3.csv"}; // ৪ নাই
        std::vector<std::string> listTwo = {"split_2.csv", "split_3.csv", "split_4.csv"}; // ১ নাই
        std::vector<std::string> listThree = {"split_1.csv", "split_3.csv", "split_4.csv"}; // ২ নাই
        std::vector<std::string> listFour = {"split_1.csv", "split_2.csv", "split_4.csv"}; // ৩ নাই
        reader.mergeCSV(listTwo,"mergedOne.csv");
        reader.mergeCSV(listThree,"mergedTwo.csv");
        reader.mergeCSV(listFour,"mergedThree.csv");
        reader.mergeCSV(listOne,"mergedFour.csv");
        CSVReader validation1("mergedOne.csv"); // ১ নাই
        CSVReader validation2("mergedTwo.csv"); // ২ নাই
        CSVReader validation3("mergedThree.csv");   // ৩ নাই
        CSVReader validation4("mergedFour.csv");    // ৪ নাই
        GradientDescent gradientDescent1("mergedOne.csv", validation1);
        GradientDescent gradientDescent2("mergedTwo.csv", validation2);
        GradientDescent gradientDescent3("mergedThree.csv", validation3);
        GradientDescent gradientDescent4("mergedFour.csv", validation4);
        std::vector<long double> coefficients1 = gradientDescent1.get_coefficients();// ১ নাই
        std::vector<long double> coefficients2 = gradientDescent2.get_coefficients();   // ২ নাই
        std::vector<long double> coefficients3 = gradientDescent3.get_coefficients();       // ৩ নাই
        std::vector<long double> coefficients4 = gradientDescent4.get_coefficients();    // ৪ নাই
        std::vector<long double> resultColumn = reader1.getColumn("Brightness");
        std::vector<long double> resultColumn2 = reader2.getColumn("Brightness");
        std::vector<long double> resultColumn3 = reader3.getColumn("Brightness");
        std::vector<long double> resultColumn4 = reader4.getColumn("Brightness");
        std::vector<long double> validationColumn1 = validation1.getColumn("Brightness");
        std::vector<long double> validationColumn2 = validation2.getColumn("Brightness");
        std::vector<long double> validationColumn3 = validation3.getColumn("Brightness");
        std::vector<long double> validationColumn4 = validation4.getColumn("Brightness");
        MatrixManipulator matrixManipulator;
        long double standardDeviationOne = matrixManipulator.standardDeviationVector(validation1.getColumn("Brightness"));
        long double standardDeviationTwo = matrixManipulator.standardDeviationVector(validation2.getColumn("Brightness"));
        long double standardDeviationThree = matrixManipulator.standardDeviationVector(validation3.getColumn("Brightness"));
        long double standardDeviationFour = matrixManipulator.standardDeviationVector(validation4.getColumn("Brightness"));
        long double levelofSignificance = 0.05;
        double accuracy=0;
        double rowNum1 = reader1.getNumberRows();
        double rowNum2 = reader2.getNumberRows();
        double rowNum3 = reader3.getNumberRows();
        double rowNum4 = reader4.getNumberRows();
        long double meanOne = matrixManipulator.meanVector(validation1.getColumn("Brightness"));
        long double meanTwo = matrixManipulator.meanVector(validation2.getColumn("Brightness"));
        long double meanThree = matrixManipulator.meanVector(validation3.getColumn("Brightness"));
        long double meanFour = matrixManipulator.meanVector(validation4.getColumn("Brightness"));
        std::vector<long double> testColumn1 = reader1.getColumn("Distance (LY)");
        std::vector<long double> testColumn2 = reader2.getColumn("Distance (LY)");
        std::vector<long double> testColumn3 = reader3.getColumn("Distance (LY)");
        std::vector<long double> testColumn4 = reader4.getColumn("Distance (LY)");
        std::vector<long double> testColumn5 = reader1.getColumn("Temperature (K)");
        std::vector<long double> testColumn6 = reader2.getColumn("Temperature (K)");
        std::vector<long double> testColumn7 = reader3.getColumn("Temperature (K)");
        std::vector<long double> testColumn8 = reader4.getColumn("Temperature (K)");
        std::vector<long double> predictedValues1;
        std::vector<long double> predictedValues2;
        std::vector<long double> predictedValues3;
        std::vector<long double> predictedValues4;
        std::vector<long double> actualValues1 ;

        std::vector<long double> actualValues2 ;

        std::vector<long double> actualValues3 ;

        std::vector<long double> actualValues4 ;
        long double count = 0;
        int it=0;
        for(int i=0;i<testColumn1.size();i++){
            if(resultColumn[i] > gradientDescent1.predictBrightness(testColumn1[i], testColumn5[i]) -(1.0- levelofSignificance) * standardDeviationOne && resultColumn[i] < gradientDescent1.predictBrightness(testColumn1[i], testColumn5[i]) + (1.0- levelofSignificance) * standardDeviationOne){
                count++;
            }
            predictedValues1.push_back(gradientDescent1.predictBrightness(testColumn1[i], testColumn5[i]));
            actualValues1.push_back(resultColumn[i]);
        }
        long double totalOne =  (long double)count /  (long double)testColumn1.size();
        count = 0;
        for(int i=0;i<testColumn2.size();i++){
            if(resultColumn2[i] > gradientDescent2.predictBrightness(testColumn2[i], testColumn6[i]) -(1.0- levelofSignificance) * standardDeviationTwo && resultColumn2[i] < gradientDescent2.predictBrightness(testColumn2[i], testColumn6[i]) + (1.0- levelofSignificance) * standardDeviationTwo){
                count++;
            }
            predictedValues2.push_back(gradientDescent2.predictBrightness(testColumn2[i], testColumn6[i]));
            actualValues2.push_back(resultColumn2[i]);
        }
        long double totalTwo = (long double) count /  (long double)testColumn2.size();
        count = 0;
        for(int i=0;i<testColumn3.size();i++){
            if(resultColumn3[i] > gradientDescent3.predictBrightness(testColumn3[i], testColumn7[i]) - (1.0- levelofSignificance) * standardDeviationThree && resultColumn3[i] < gradientDescent3.predictBrightness(testColumn3[i], testColumn7[i]) + (1.0- levelofSignificance) * standardDeviationThree){
                count++;
            }
            predictedValues3.push_back(gradientDescent3.predictBrightness(testColumn3[i], testColumn7[i]));
            actualValues3.push_back(resultColumn3[i]);
        }
        long double totalThree =  (long double)count / (long double)testColumn3.size();
        count = 0;
        for(int i=0;i<testColumn4.size();i++){
            if(resultColumn4[i] > gradientDescent4.predictBrightness(testColumn4[i], testColumn8[i]) - (1.0- levelofSignificance) * standardDeviationFour && resultColumn4[i] < gradientDescent4.predictBrightness(testColumn4[i], testColumn8[i]) + (1.0- levelofSignificance) * standardDeviationFour){
                count++;
            }
            predictedValues4.push_back(gradientDescent4.predictBrightness(testColumn4[i], testColumn8[i]));
            actualValues4.push_back(resultColumn4[i]);
        }
        long double totalFour =  (long double)count /  (long double)testColumn4.size();
        count = 0;
        std::cout << "Accuracy of 1st split: " << totalOne << std::endl;
        std::cout << "Accuracy of 2nd split: " << totalTwo << std::endl;
        std::cout << "Accuracy of 3rd split: " << totalThree << std::endl;
        std::cout << "Accuracy of 4th split: " << totalFour << std::endl;
        std::cout << "Average accuracy: " << (totalOne + totalTwo + totalThree + totalFour) / 4.0 << std::endl;
        double rSquared1 = calculateRSquared(actualValues1, predictedValues1);
        double rSquared2 = calculateRSquared(actualValues2, predictedValues2);
        double rSquared3 = calculateRSquared(actualValues3, predictedValues3);
        double rSquared4 = calculateRSquared(actualValues4, predictedValues4);

        std::cout << "R-squared of 1st split: " << rSquared1 << std::endl;
        std::cout << "R-squared of 2nd split: " << rSquared2 << std::endl;
        std::cout << "R-squared of 3rd split: " << rSquared3 << std::endl;
        std::cout << "R-squared of 4th split: " << rSquared4 << std::endl;
        std::cout << "Average R-squared: " << (rSquared1 + rSquared2 + rSquared3 + rSquared4) / 4.0 << std::endl;
    }


    long double calculateRSquared(const std::vector<long double>& actual, const std::vector<long double>& predicted) {
        long double meanActual = std::accumulate(actual.begin(), actual.end(), 0.0) / actual.size();

        long double totalSumSquares = 0.0;
        for (long double actualValue : actual) {
            totalSumSquares += std::pow(actualValue - meanActual, 2);
        }

        long double residualSumSquares = 0.0;
        for (size_t i = 0; i < actual.size(); ++i) {
            residualSumSquares += std::pow(actual[i] - predicted[i], 2);
        }

        double rSquared = 1.0 - (residualSumSquares / totalSumSquares);

        return rSquared;
    }

};
#endif //SPL_01_CROSSVALIDATION_H
