#ifndef IMAGE_HPP
#define IMAGE_HPP
#include "Color.hpp"
class Image
{
public:
    //atribute
    Color *colorData;
    unsigned char *greyData;
    int width;
    int height;
    int size;
    bool isColor;
    
    //constructor
    Image(int width, int height, bool isColor);
    
    //destroyer
    ~Image();

    //data constructor
    void createColorData();
    void createGreyData();

    //data destructor
    void deleteColorData();
    void deleteGreyData();

    //method setColorData
    void setColorData(int x, int y, unsigned char R, unsigned char G, unsigned char B);
    
    //method setGreyData
    void setGreyData(int x, int y, unsigned char grey);

    //method getColorData
    Color getColorData(int x, int y);

    //method getGreyData
    unsigned char getGreyData(int x, int y);
};
#endif