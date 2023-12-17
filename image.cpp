//
// Created by ASUS on 12/16/2023.
//

#include "Image.h"
#include "iostream"
#include "fstream"
#include "cmath"
#include "Image.h"
#include "string"
#include "Stacker.h"
#include "threadStacker.h"
#include <iomanip>
#include "DirectoryReader.h"
#include"CSVReader.h"
#include"crossValidation.h"
#include "GradientDescent.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "vector"
Color::Color(): red(0),green(0),blue(0)
{
}
Color::Color(float red,float green,float blue):red(red),green(green),blue(blue)
{
}
Color::~Color()
{
}
Image::Image(int width, int height):m_width(width),m_height(height),m_colors(std::vector<Color>(width*height))
{
}
Image::~Image()
{
};
Color Image::GetColor(int x, int y) const
{
    return m_colors[y*m_width+x];
}
void Image::SetColor(const Color &color, int x, int y)
{
    m_colors[y*m_width+x].red = color.red;
    m_colors[y*m_width+x].green = color.green;
    m_colors[y*m_width+x].blue = color.blue;
}
void Image::Read(const char* path)
{
    std::ifstream file;
    file.open(path,std::ios::in | std::ios::binary);
    if(!file.is_open())
    {
        std::cout << "file can't be opened"<<std::endl;
        return;
    }
    const int fileHeaderSize=14;
    const int informationHeadersize = 40;
    unsigned  char fileHeader[fileHeaderSize];
    file.read(reinterpret_cast<char *>(fileHeader),fileHeaderSize);
    unsigned char informationHeader[informationHeadersize];
    file.read(reinterpret_cast<char*>(informationHeader),informationHeadersize);
    int fileSize = fileHeader[2]+ (fileHeader[3]<<8)+(fileHeader[4]<<16)+(fileHeader[5]<<24);
    m_width = informationHeader[4]+(informationHeader[5]<<8) + (informationHeader[6]<<16)+(informationHeader[7]<<24);
    m_height=informationHeader[8]+(informationHeader[9]<<8) + (informationHeader[10]<<16)+(informationHeader[11]<<24);
    m_colors.resize(m_width*m_height);
    const int padddingAmount = ((4-(m_width*3)%4)%4);
    for(int y=0;y<m_height;y++)
    {
        for(int x = 0;x<m_width;x++)
        {
            unsigned char color[3];
            file.read(reinterpret_cast<char*>(color),3);
            m_colors[y*m_width+x].red = static_cast<float>(color[0])/255.0f;
            m_colors[y*m_width+x].green =  static_cast<float>(color[1])/255.0f;
            m_colors[y*m_width+x].blue =  static_cast<float>(color[2])/255.0f;
            file.ignore(padddingAmount);
        }
    }
    file.close();
    // std::cout <<"file has been read";
}
void Image::Export(const char *path) const
{
    std::ofstream file;
    file.open(path,std::ios::out | std::ios::binary);
    if(!file.is_open())
    {
        std::cout << "File is not opened";
        return;
    }

    unsigned char bmpPad[3] = {0,0,0};
    const int padddingAmount = ((4-(m_width*3)%4)%4);
    const int fileHeaderSize= 14;
    const int informationHeaderSize = 40;
    const int filesize = fileHeaderSize+informationHeaderSize+m_width*m_height*3+padddingAmount*m_width;
    unsigned char fileHeader[fileHeaderSize];
    //Type
    fileHeader[0]='B';
    fileHeader[1] = 'M';
    //Size
    fileHeader[2]=filesize;
    fileHeader[3]=filesize>>8;
    fileHeader[4]=filesize>>16;
    fileHeader[5]=filesize>>24;
    //reserved
    fileHeader[6]=0;
    fileHeader[7]=0;
    //reserved2
    fileHeader[8]=0;
    fileHeader[9]=0;
    //pixeldata offset
    fileHeader[10] = fileHeaderSize+informationHeaderSize;
    fileHeader[11]=0;
    fileHeader[12]=0;
    fileHeader[13]=0;

    unsigned char informationHeader[informationHeaderSize];
    //Headersize
    informationHeader[0]=informationHeaderSize;
    informationHeader[1]=0;
    informationHeader[2]=0;
    informationHeader[3]=0;
    //image width
    informationHeader[4]=m_width;
    informationHeader[5]=m_width>>8;
    informationHeader[6]=m_width >>16;
    informationHeader[7]=m_width>>24;
    //image height
    informationHeader[8]=m_height;
    informationHeader[9]=m_height>>8;
    informationHeader[10]=m_height>>16;
    informationHeader[11]=m_height>>24;
    //planes
    informationHeader[12]=1;
    informationHeader[13]=0;
    //bits per pixel
    informationHeader[14]=24;
    informationHeader[15]=0;
    informationHeader[16]=0;
    informationHeader[17]=0;
    informationHeader[18]=0;
    informationHeader[19]=0;
    informationHeader[20]=0;
    informationHeader[21]=0;
    informationHeader[22]=0;
    informationHeader[23]=0;
    informationHeader[24]=0;
    informationHeader[25]=0;
    informationHeader[26]=0;
    informationHeader[27]=0;
    informationHeader[28]=0;
    informationHeader[29]=0;
    informationHeader[30]=0;
    informationHeader[31]=0;
    informationHeader[32]=0;
    informationHeader[33]=0;
    informationHeader[34]=0;
    informationHeader[35]=0;
    informationHeader[36]=0;
    informationHeader[37]=0;
    informationHeader[38]=0;
    informationHeader[39]=0;
    file.write(reinterpret_cast<char*>(fileHeader),fileHeaderSize);
    file.write(reinterpret_cast<char*>(informationHeader),informationHeaderSize);
    for(int y=0;y<m_height;y++)
    {
        for(int x = 0;x<m_width;x++)
        {
            unsigned char red = static_cast<unsigned char>(GetColor(x,y).red*255.0f);
            unsigned char green = static_cast<unsigned char>(GetColor(x,y).green*255.0f);
            unsigned char blue = static_cast<unsigned char>(GetColor(x,y).blue*255.0f);
            unsigned char color[]={red,green,blue};
            file.write(reinterpret_cast<char*>(color),3);
        }
        file.write(reinterpret_cast<char*>(bmpPad),padddingAmount);
    }
    file.close();
    std::cout << "created"<<std::endl;
}
int Image::getMWidth() const
{
    return m_width;
}
int Image::getMHeight() const
{
    return m_height;
}
const std::vector<Color> &Image::getMColors() const
{
    return m_colors;
}
void Image::setMColors(const std::vector<Color> &mColors)
{
    m_colors = mColors;
}
Color Image::Convolution(const std::vector<Color>& neighborhood, const int kernel[3][3])
{
    float redSum = 0.0f, greenSum = 0.0f, blueSum = 0.0f;
    int index = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            redSum += neighborhood[index].red * kernel[i][j];
            greenSum += neighborhood[index].green * kernel[i][j];
            blueSum += neighborhood[index].blue * kernel[i][j];
            ++index;
        }
    }
    return Color(redSum, greenSum, blueSum);
}
void Image::EdgeDetectionUsingSobelOperator(Image& edgeDetectedImage)
{
    const int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    const int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    Image resultImage(edgeDetectedImage.getMWidth(), edgeDetectedImage.getMHeight());
    for (int y = 1; y < edgeDetectedImage.getMHeight() - 1; ++y)
    {
        for (int x = 1; x < edgeDetectedImage.getMWidth() - 1; ++x)
        {
            std::vector<Color> neighborhoodX, neighborhoodY;
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    neighborhoodX.push_back(edgeDetectedImage.GetColor(x + i, y + j));
                    neighborhoodY.push_back(edgeDetectedImage.GetColor(x + i, y + j));
                }
            }
            Color convX = Convolution(neighborhoodX, sobelX);
            Color convY = Convolution(neighborhoodY, sobelY);
            float gradientMagnitude = sqrt(convX.red * convX.red + convY.red * convY.red);
            float intensity = gradientMagnitude > 0.3f ? 1.0f : 0.0f;
            resultImage.SetColor(Color(intensity, intensity, intensity), x, y);
        }
    }
    resultImage.Export("D:\\Academic\\ObjectDetected.bmp");
}
