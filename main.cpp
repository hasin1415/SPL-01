#include "Image.h"
#include "string"
#include "Stacker.h"
#include <iomanip>
#include"CSVReader.h"
#include"crossValidation.h"
#include "GradientDescent.h"
#include <iostream>
#include "CoordinateCalc.h"
using namespace std;
void ImageStacker(std::string path)
{
    Stacker stacker(path);
    std::vector<Image> images = stacker.getImages();
    ThreadStacker threadStacker;
    Image a = threadStacker.sumImagesWithThreads(images);
    a.Export("D:\\Academic\\result.bmp");
}
void galacticRegression()
{
    string path;
    cout << "Enter the path of the csv file" << endl;
    cin >> path;
    CSVReader reader(path);
    cout << "Do you want to see accuracy of the model? (y/n)" << endl;
    string input;
    cin >> input;
    if(input=="y")
    {
        crossValidation crossValidation(path, reader);
    }
    else if(input=="n")
    {
        cout << "Ok" << endl;
    }
    else
    {
        cout << "Wrong input" << endl;
    }
    long double distance, temperature;
    cout << "Enter the distance and temperature" << endl;
    cin >> distance >> temperature;
    GradientDescent gradientDescent(path, reader);
    std::vector<long double> coefficients = gradientDescent.get_coefficients();
    std::cout << "Coefficients: " << coefficients[0] << " " << coefficients[1] << " " << coefficients[2] << std::endl;
    std::cout << gradientDescent.predictBrightness(distance, temperature) << " solar luminosity"<<std::endl;
    std::cout << "finished" << std::endl;
}
void celestialObjectDetection()
{
    string path;
    cout << "Enter the path of the image" << endl;
    cin >> path;
    Image image(0, 0);
    image.Read(path.c_str());
    image.EdgeDetectionUsingSobelOperator(image);
}
void CoordinateCalc(){
    class CoordinateCalc coordinateCalc;
    double ra, dec, lambda, beta, parallaxRA, parallaxDec, distance;
    cout << "Enter the RA and DEC" << endl;
    cin >> ra >> dec;
    cout << "Enter the distance" << endl;
    cin >> distance;
    coordinateCalc.equatorialToEcliptic(ra, dec, lambda, beta);
    cout << "lambda: " << lambda << " beta: " << beta << endl;
    coordinateCalc.calculateParallax(ra, dec, distance, parallaxRA, parallaxDec);
    cout << "parallaxRA: " << parallaxRA << " parallaxDec: " << parallaxDec << endl;
    coordinateCalc.eclipticToEquatorial(lambda, beta, ra, dec);
    cout << "ra: " << ra << " dec: " << dec << endl;
}
bool menu()
{
    bool test = true;
    std::cout << "     /\\                                  /\\" << std::endl;
    std::cout << "____/  \\____                        ____/  \\____ " << std::endl;
    std::cout << "\\          /                        \\          /" << std::endl;
    std::cout << " >        <   Astronomy Engine Menu  >        <  " << std::endl;
    std::cout << "/___    ___\\                        /___    ___\\ " << std::endl;
    std::cout << "    \\  /                                \\  /    " << std::endl;
    std::cout << "     \\/                                  \\/     " << std::endl;
    std::cout << std::setfill('*') << std::setw(5) << '*' << std::setw(25) << "1. Starry Image Stacker" << std::setw(19) << '*' << std::endl;
    std::cout << std::setfill('*') << std::setw(5) << '*' << std::setw(25) << "2. Celestial Object Detection" << std::setw(15) << '*' << std::endl;
    std::cout << std::setfill('*') << std::setw(5) << '*' << std::setw(25) << "3. Galactic Regression" << std::setw(19) << '*' << std::endl;
    std::cout << std::setfill('*') << std::setw(5) << '*' << std::setw(25) << "4. AstroCalculator" << std::setw(19) << '*' << std::endl;
    std::cout << std::setfill('*') << std::setw(5) << '*' << std::setw(20) << "5. exit" << std::setw(24) << '*' << std::endl;
    std::cout << std::setw(49) << std::setfill('*') << '*' << std::endl;
    std::cout << "          type what you want to open      "  << std::endl;
    std::cout << std::setw(49) << std::setfill('*') << '*' << std::endl;
    std::string input;
    std::cin >> input;
    if(input=="1"){
        std::cout << "Starry Image Stacker is opening" << std::endl;
        std::string path;
        std::cout << "Enter the path of the images" << std::endl;
        std::cin >> path;
        std::cout<<"Processing..."<<std::endl;
        ImageStacker("D:\\threadtuktak\\cmake-build-debug\\images");
    }
    else if(input=="2")
    {
        std::cout << "Celestial Object Detection is opening" << std::endl;
        celestialObjectDetection();
        std::cout<<"finished"<<std::endl;
    }
    else if(input=="3")
    {
        std::cout << "Galactic Regression is opening" << std::endl;
        galacticRegression();
    }
    else if(input=="4")
    {
        std::cout << "AstroCalculator is opening" << std::endl;
        CoordinateCalc();
        std::cout<<"finished"<<std::endl;
    }
    else if(input=="5")
    {
        std::cout << "Exiting" << std::endl;
        test = false;
    }
    else
    {
        std::cout << "Wrong input" << std::endl;
    }
    return test;
}
int main(){
    while(1)
    {
        if(menu())
        {
            continue;
        }
        else{
            break;
        }
    }
    return 0;
}
