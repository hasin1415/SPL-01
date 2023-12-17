//
// Created by ASUS on 12/16/2023.
//

#ifndef SPL_01_IMAGE_H
#define SPL_01_IMAGE_H

#include "string"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "vector"
struct Color{
    float red, green ,blue;
    Color();
    Color(float red,float green,float blue);
    ~Color();
};
class Image{
public:
    int getMWidth() const;
    int getMHeight() const;
    const std::vector<Color> &getMColors() const;
    void setMColors(const std::vector<Color> &mColors);
    Image(int width,int height);
    ~Image();
    Color GetColor(int x, int y)const;
    void SetColor(const Color& color , int x , int y);
    void Export(const char * path)const;
    void Read(const char* path);
    void EdgeDetectionUsingSobelOperator(Image& edgeDetectedImage);
    Color Convolution(const std::vector<Color>& neighborhood, const int kernel[3][3]) ;
private:
    int m_width;
    int m_height;
    std::vector<Color> m_colors;
};


#endif //SPL_01_IMAGE_H
