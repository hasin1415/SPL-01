//
// Created by ASUS on 9/7/2023.
//

#ifndef SPL_01_STACKER_H
#define SPL_01_STACKER_H
#include "image.h"
#include "iostream"

class Stacker {
    Image imageOne;
    Image imageTwo;
    Image outputImage;
    public:
    Stacker(Image imageOne, Image imageTwo) {
        this->imageOne = *new Image(imageOne);
        this->imageTwo = *new Image(imageTwo);
    };
    Image stackImages(){
        if(imageOne.getMHeight()!= imageTwo.getMHeight() || imageOne.getMWidth() != imageTwo.getMWidth()){
            std::cout << "The images must have the same dimensions." << std::endl;
            exit(1);
        }
        else{
            outputImage = *new Image(imageOne.getMHeight(), imageOne.getMWidth());
            for (int i = 0; i < imageOne.getMHeight(); i++) {
                for (int j = 0; j < imageOne.getMWidth(); j++) {
                    outputImage.SetColor(Color(),i,j);
                }
            }

        }

    }



};


#endif //SPL_01_STACKER_H
