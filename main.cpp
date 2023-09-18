#include "image.h"
#include "string"
#include "directoryReader.h"
#include <iostream>
#include <filesystem>


using namespace std;
int main(){
    const int width = 680;
    const int height = 480;
    Image image(width,height);
    directoryReader  Obj = *new directoryReader("D:\\");
    std::vector<std::string> fileNames;
     vector<string> files =  Obj.Directories(fileNames);

  for(int y=0;y<height;y++){
        for(int x = 0;x<width;x++){
            image.SetColor(Color((float)x/(float)width,1.0f-((float)x/(float)width),(float )y/(float)height),x,y);
        }
    }
    image.Export("image.bmp");
    Image copy(0,0);
    copy.Read("a.bmp");
    copy.Export("copy.bmp");*/
   create_directory("D:\\test");
}