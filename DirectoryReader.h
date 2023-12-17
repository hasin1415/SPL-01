//
// Created by ASUS on 12/16/2023.
//

#ifndef SPL_01_DIRECTORYREADER_H
#define SPL_01_DIRECTORYREADER_H


#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "bits/stdc++.h"
#include "Image.h"
#include "string"
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "vector"
namespace fs = std::filesystem;

class DirectoryReader{
private:
    std::string fName;
    std::vector<std::string> fileNames;

public:
    DirectoryReader(std::string fName) : fName(std::move(fName)) {}

    const std::string &getFName() const
    {
        return fName;
    }

    void setFName(const std::string &fName) {
        DirectoryReader::fName = fName;
    }

    void setFileNames(const std::vector<std::string> &fileNames) {
        DirectoryReader::fileNames = fileNames;
    }

    std::vector<std::string> getDirectories() {
        try {
            for (const auto& entry : fs::directory_iterator(fName)) {
                if (entry.is_directory()) {
                    fileNames.push_back(entry.path().filename().string());
                } else if (entry.is_regular_file()) {
                    fileNames.push_back(entry.path().filename().string());
                }
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        fileNames = filterBMP(fileNames);
        //std::cout <<"getDirectories"<< std::endl;
        return fileNames;
    }

    const std::vector<std::string>& getFileNames() {
        fileNames = getDirectories();
        return fileNames;
    }
    std::vector<std::string> filterBMP(std::vector<std::string> fileNames){
        std::vector<std::string> bmpFiles;
        for (const std::string& fileName : fileNames) {
            std::string extension = fileName.substr(fileName.find_last_of(".") + 1);
            if (extension == "bmp") {
                bmpFiles.push_back(fileName);
            }
        }
        //   std::cout<<"filterBMP"<<std::endl;
        return bmpFiles;
    }
    void removeFiles(std::vector<std::string> fileNames){
        for (const std::string& fileName : fileNames) {
            std::string extension = fileName.substr(fileName.find_last_of(".") + 1);
            if (extension != "bmp") {
                fs::remove(fileName);
            }
        }
    }
};

#endif //SPL_01_DIRECTORYREADER_H
