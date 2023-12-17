//
// Created by ASUS on 12/16/2023.
//

#ifndef SPL_01_STACKER_H
#define SPL_01_STACKER_H


#include "Image.h"
#include "iostream"
#include "bits/stdc++.h"
#include "DirectoryReader.h"
#include "ThreadStacker.h"

class Stacker {
private:
    std::vector<Image> images;
    std::string filepaths;
public:
    Stacker(const std::string &filepaths) : filepaths(filepaths) {
        DirectoryReader directoryReader(filepaths);
        std::vector<std::string> fileNames = directoryReader.getFileNames();
        for (const std::string &fileName : fileNames) {
            Image image(0,0);
            std::string str = directoryReader.getFName() + "\\" + fileName;
            image.Read(str.c_str());
            //  std::cout<< str.c_str();
            images.push_back(image);
        }
        if(!checkSize()){
            std::cout << "Images are not the same size" << std::endl;
            exit(0);
        }
    }
    const std::vector<Image> &getImages() const {
        return images;
    }
    void setImages(const std::vector<Image> &images) {
        Stacker::images = images;
    }
    bool checkSize(){
        int width = images[0].getMWidth();
        int height = images[0].getMHeight();
        for (const Image &image : images) {
            if(image.getMWidth()!=width || image.getMHeight()!=height){
                return false;
            }
        }
        return true;
    }
};


#endif //SPL_01_STACKER_H
