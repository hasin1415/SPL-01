//
// Created by ASUS on 9/7/2023.
//

#ifndef SPL_01_STACKER_H
#define SPL_01_STACKER_H
#include "image.h"


class Stacker {
    public:
    image img;
    Stacker(image img) {
        this->img = img;
    };
    void stacker(int x, int y, int width, int height, int n, std::string filename) {
        image imgNew = image(width, height);
        for (int i = 0; i < n; i++) {
            imgNew.copyImage(img, x, y, width, height, i * width, i * height);
        }
        imgNew.saveImage(filename);
    }




};


#endif //SPL_01_STACKER_H
