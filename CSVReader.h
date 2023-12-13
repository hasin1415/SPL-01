//
// Created by ASUS on 12/13/2023.
//

#ifndef SPL_01_CSVREADER_H
#define SPL_01_CSVREADER_H

#include "bits/stdc++.h"

class CSVReader {
private:
    std::string filePath;
    std::vector<std::string> headers;
    std::vector<std::vector<long double>> columns;
    int numRows; // Added numRows

public:
    CSVReader(const std::string& path) : filePath(path), numRows(0) {
        readCSV();
    }
    void readCSV() {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        std::string line, cell;
        // Read header
        if (std::getline(file, line)) {
            std::stringstream headerStream(line);
            while (std::getline(headerStream, cell, ',')) {
                headers.push_back(cell);
                columns.push_back(std::vector<long double>{});
            }
        }

        // Read data
        while (std::getline(file, line)) {
            std::stringstream lineStream(line);
            int colIdx = 0;
            while (std::getline(lineStream, cell, ',')) {
                try {
                    long double value = std::stod(cell);
                    columns[colIdx].push_back(value);
                } catch (...) {
                    // Handle conversion errors or non-numeric data
                    // For simplicity, you might choose to skip or handle errors differently
                    columns[colIdx].push_back(0.0); // Placeholder value
                }
                colIdx++;
            }
            numRows++; // Increment numRows for each row read
        }
        file.close();
    }

    std::vector<long double> getColumn(const std::string& nameColumn) {
        auto it = std::find(headers.begin(), headers.end(), nameColumn);
        if (it != headers.end()) {
            int index = std::distance(headers.begin(), it);
            return columns[index];
        } else {
            std::cerr << "Column '" << nameColumn << "' not found!" << std::endl;
            return std::vector<long double>{};
        }
    }
    int getNumberRows() const {
        return numRows;
    }
    void csvSplitter() {
        // Ensure there's enough data to split
        if (numRows < 4) {
            std::cerr << "Insufficient data to split into 4 files." << std::endl;
            return;
        }

        int rowsPerFile = std::ceil(static_cast<long double>(numRows) / 4);
        for (int fileIdx = 0; fileIdx < 4; ++fileIdx) {
            std::string outputFileName = "split_" + std::to_string(fileIdx + 1) + ".csv";
            std::ofstream outputFile(outputFileName);

            // Write headers to each file
            for (const std::string& header : headers) {
                outputFile << header << ",";
            }
            outputFile << std::endl;

            // Determine range of rows for this file
            int startRow = fileIdx * rowsPerFile;
            int endRow = std::min((fileIdx + 1) * rowsPerFile, numRows);

            // Write data rows to the file
            for (int row = startRow; row < endRow; ++row) {
                for (size_t col = 0; col < columns.size(); ++col) {
                    outputFile << columns[col][row];
                    if (col != columns.size() - 1) {
                        outputFile << ",";
                    }
                }
                outputFile << std::endl;
            }

            outputFile.close();
        }
    }
    void deleteSplitFile(const std::string& splitFileName) {
        if (std::remove(splitFileName.c_str()) != 0) {
            std::cerr << "Error deleting file: " << splitFileName << std::endl;
        } else {
            std::cout << "File deleted successfully: " << splitFileName << std::endl;
        }
    }

    const std::string &getFilePath() const {
        return filePath;
    }

    void setFilePath(const std::string &filePath) {
        CSVReader::filePath = filePath;
    }

    const std::vector<std::string> &getHeaders() const {
        return headers;
    }

    void setHeaders(const std::vector<std::string> &headers) {
        CSVReader::headers = headers;
    }

    const std::vector<std::vector<long double>> &getColumns() const {
        return columns;
    }

    void setColumns(const std::vector<std::vector<long double>> &columns) {
        CSVReader::columns = columns;
    }

    int getNumRows() const {
        return numRows;
    }

    void setNumRows(int numRows) {
        CSVReader::numRows = numRows;
    }
    void mergeCSV(const std::vector<std::string>& filenames, const std::string& mergedFileName) {
        std::ofstream mergedFile(mergedFileName);
        if (!mergedFile.is_open()) {
            std::cerr << "Error creating the merged file." << std::endl;
            return;
        }

        bool skipHeader = false;

        for (const auto& filename : filenames) {
            std::ifstream fileToMerge(filename);
            if (!fileToMerge.is_open()) {
                std::cerr << "Error opening file: " << filename << std::endl;
                continue;
            }

            if (skipHeader) {
                // Skip the header line
                std::string header;
                std::getline(fileToMerge, header);
            } else {
                // Copy content from the first file (which contains the header)
                mergedFile << fileToMerge.rdbuf();
                skipHeader = true; // Set flag to skip headers for subsequent files
            }
            // Copy the content except the header line
            std::copy(std::istreambuf_iterator<char>(fileToMerge), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(mergedFile));
            fileToMerge.close();
        }
        mergedFile.close();
    }
};


#endif //SPL_01_CSVREADER_H
