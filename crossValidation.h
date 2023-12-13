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
        std::vector<long double> resultColumn = reader1.getColumn("SalePrice");
        std::vector<long double> resultColumn2 = reader2.getColumn("SalePrice");
        std::vector<long double> resultColumn3 = reader3.getColumn("SalePrice");
        std::vector<long double> resultColumn4 = reader4.getColumn("SalePrice");
        std::vector<long double> validationColumn1 = validation1.getColumn("SalePrice");
        std::vector<long double> validationColumn2 = validation2.getColumn("SalePrice");
        std::vector<long double> validationColumn3 = validation3.getColumn("SalePrice");
        std::vector<long double> validationColumn4 = validation4.getColumn("SalePrice");
        MatrixManipulator matrixManipulator;
        long double standardDeviationOne = matrixManipulator.standardDeviationVector(validation1.getColumn("SalePrice"));
        long double standardDeviationTwo = matrixManipulator.standardDeviationVector(validation2.getColumn("SalePrice"));
        long double standardDeviationThree = matrixManipulator.standardDeviationVector(validation3.getColumn("SalePrice"));
        long double standardDeviationFour = matrixManipulator.standardDeviationVector(validation4.getColumn("SalePrice"));
        long double levelofSignificance = 0.05;
        double accuracy=0;
        double rowNum1 = reader1.getNumberRows();
        double rowNum2 = reader2.getNumberRows();
        double rowNum3 = reader3.getNumberRows();
        double rowNum4 = reader4.getNumberRows();
        long double meanOne = matrixManipulator.meanVector(validation1.getColumn("SalePrice"));
        long double meanTwo = matrixManipulator.meanVector(validation2.getColumn("SalePrice"));
        long double meanThree = matrixManipulator.meanVector(validation3.getColumn("SalePrice"));
        long double meanFour = matrixManipulator.meanVector(validation4.getColumn("SalePrice"));
        std::vector<long double> testColumn1 = reader1.getColumn("GrLivArea");
        std::vector<long double> testColumn2 = reader2.getColumn("GrLivArea");
        std::vector<long double> testColumn3 = reader3.getColumn("GrLivArea");
        std::vector<long double> testColumn4 = reader4.getColumn("GrLivArea");
        std::vector<long double> testColumn5 = reader1.getColumn("TotalBsmtSF");
        std::vector<long double> testColumn6 = reader2.getColumn("TotalBsmtSF");
        std::vector<long double> testColumn7 = reader3.getColumn("TotalBsmtSF");
        std::vector<long double> testColumn8 = reader4.getColumn("TotalBsmtSF");
        long double count = 0;
        int it=0;
        for(int i=0;i<testColumn1.size();i++){
            if(resultColumn[i] > gradientDescent1.predictSalePrice(testColumn1[i], testColumn5[i]) -(1.0- levelofSignificance) * standardDeviationOne && resultColumn[i] < gradientDescent1.predictSalePrice(testColumn1[i], testColumn5[i]) + (1.0- levelofSignificance) * standardDeviationOne){
                count++;
            }
        }
        long double totalOne =  (long double)count /  (long double)testColumn1.size();
        count = 0;
        for(int i=0;i<testColumn2.size();i++){
            if(resultColumn2[i] > gradientDescent2.predictSalePrice(testColumn2[i], testColumn6[i]) -(1.0- levelofSignificance) * standardDeviationTwo && resultColumn2[i] < gradientDescent2.predictSalePrice(testColumn2[i], testColumn6[i]) + (1.0- levelofSignificance) * standardDeviationTwo){
                count++;
            }
        }
        long double totalTwo = (long double) count /  (long double)testColumn2.size();
        count = 0;
        for(int i=0;i<testColumn3.size();i++){
            if(resultColumn3[i] > gradientDescent3.predictSalePrice(testColumn3[i], testColumn7[i]) - (1.0- levelofSignificance) * standardDeviationThree && resultColumn3[i] < gradientDescent3.predictSalePrice(testColumn3[i], testColumn7[i]) + (1.0- levelofSignificance) * standardDeviationThree){
                count++;
            }
        }
        long double totalThree =  (long double)count / (long double)testColumn3.size();
        count = 0;
        for(int i=0;i<testColumn4.size();i++){
            if(resultColumn4[i] > gradientDescent4.predictSalePrice(testColumn4[i], testColumn8[i]) - (1.0- levelofSignificance) * standardDeviationFour && resultColumn4[i] < gradientDescent4.predictSalePrice(testColumn4[i], testColumn8[i]) + (1.0- levelofSignificance) * standardDeviationFour){
                count++;
            }
        }
        long double totalFour =  (long double)count /  (long double)testColumn4.size();
        count = 0;
        std::cout << "Accuracy of 1st split: " << totalOne << std::endl;
        std::cout << "Accuracy of 2nd split: " << totalTwo << std::endl;
        std::cout << "Accuracy of 3rd split: " << totalThree << std::endl;
        std::cout << "Accuracy of 4th split: " << totalFour << std::endl;
        std::cout << "Average accuracy: " << (totalOne + totalTwo + totalThree + totalFour) / 4.0 << std::endl;
    }
};

#endif //SPL_01_CROSSVALIDATION_H
