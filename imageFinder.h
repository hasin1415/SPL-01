//
// Created by ASUS on 9/18/2023.
//

#ifndef SPL_01_IMAGEFINDER_H
#define SPL_01_IMAGEFINDER_H
#include "directoryReader.h"
#include "vector"
#include "string"
#include <filesystem>

class imageFinder {
private:
    std::vector<std::string> fileNames;
    std::vector<std::string> files ;
    std::vector<std::string> imageNames;
    std::vector<std::string> imageExtensions;
public:
    imageFinder(std::string path){
        directoryReader dr = directoryReader(path);
        fileNames = dr.getFileNames();
        files = dr.getFiles();
        getImages(files);
    }
    std::vector<std::string>getFileNames(){
        return fileNames;
    }
    std::vector<std::string>getFiles(){
        return files;
    }
    std::vector<std::string> getImageNames(){
        return imageNames;
    }
    std::vector<std::string> getImageExtensions(){
        return imageExtensions;
    }
    void getImages(std::vector<std::string> files){
        for (const std::string& fileName : files) {
            std::string extension = fileName.substr(fileName.find_last_of(".") + 1);
            if (extension == "bmp") {
                imageNames.push_back(fileName);
                imageExtensions.push_back(extension);
            }
        }
    }
};


#endif //SPL_01_IMAGEFINDER_H
