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

/*
 *     for(int y=0;y<One.getMHeight();y++){
        for(int x = 0;x<One.getMWidth();x++){
            Color color1 = One.GetColor(x,y);
            Color color2 = Two.GetColor(x,y);
            result.SetColor(Color((color1.red+color2.red)/2.0,(color1.green+color2.green)/2.0,(color1.blue+color2.blue)/2.0),x,y);
            Color color3 = three.GetColor(x,y);
            Color ik = result.GetColor(x,y);
            result.SetColor(Color((ik.red+color3.red)/2,(ik.green+color3.green)/2,(ik.blue+color3.blue)/2),x,y);
            Color color4 = four.GetColor(x,y);
            ik = result.GetColor(x,y);
            result.SetColor(Color((ik.red+color4.red)/2,(ik.green+color4.green)/2,(ik.blue+color4.blue)/2),x,y);
            Color color5 = five.GetColor(x,y);
            ik = result.GetColor(x,y);
            result.SetColor(Color((ik.red+color5.red)/2,(ik.green+color5.green)/2,(ik.blue+color5.blue)/2),x,y);
            //result.SetColor(Color((color1.red+color2.red+color3.red+color4.red+color5.red)/5.0,(color1.green+color2.green+color3.green+color4.green+color5.green)/5.0,(color1.blue+color2.blue+color3.blue+color4.blue+color5.blue)/5.0),x,y);
        }
    }
*/
};


#endif //SPL_01_STACKER_H
