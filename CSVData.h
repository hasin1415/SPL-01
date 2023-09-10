//
// Created by ASUS on 9/9/2023.
//

#ifndef SPL_01_CSVDATA_H
#define SPL_01_CSVDATA_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class CSVData {
public:
    std::vector<std::string> headers;
    std::vector<std::vector<double>> data;
    void printData(){
        for (const std::string &header : headers) {
            std::cout << header << " ";
        }
        std::cout << std::endl;

        for (const std::vector<double> &row : data) {
            for (double value : row) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
    }
};

void readCSV(const std::string &filename, CSVData &csvData) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    bool isHeader = true;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<double> row;
        while (std::getline(iss, token, ',')) {
            if (isHeader) {
                csvData.headers.push_back(token);
            } else {
                double value = std::stod(token); // Convert string to double
                row.push_back(value);
            }
        }

        if (!isHeader) {
            csvData.data.push_back(row);
        }

        isHeader = false;
    }

    file.close();
}


#endif //SPL_01_CSVDATA_H
