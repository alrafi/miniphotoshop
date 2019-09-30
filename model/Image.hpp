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
    Image();
    Image(int width, int height, bool isColor);
    
    //destroyer
    ~Image();

    //data constructor
    void createColorData();
    void createGreyData();

    //data destructor
    void deleteColorData();
    void deleteGreyData();

    //setter attribute
    void setWidth(int width);
    void setHeight(int height);
    void setColor(bool isColor);
    
    //call this method when you want to update size of image, this func will set the size with updated width and updated heigth
    void updateSize();

    //method setColorData
    void setColorData(int x, int y, unsigned char R, unsigned char G, unsigned char B);
    
    //method setGreyData
    void setGreyData(int x, int y, unsigned char grey);

    //method setColorData by Index
    void setColorDataByIndex(int index, unsigned char R, unsigned char G, unsigned char B);
    
    //method setGreyData by Index
    void setGreyDataByIndex(int index, unsigned char grey);

    //method to getcolordata by index
    Color getColorDataByIndex(int index);

    //method to getgreydata by index
    unsigned char getGreyDataByIndex(int index);

    //method getColorData
    Color getColorData(int x, int y);

    //method getGreyData
    unsigned char getGreyData(int x, int y);

    unsigned char* getRedData();
    unsigned char* getGreenData();
    unsigned char* getBlueData();

    //method operator image
    Image operator+(Image const &img);
    Image operator+(int scalar);
    Image operator-(Image const &img);
    Image operator-(int scalar);
    Image& operator=(const Image &img);
    Image operator*(const Image &img);
    Image operator*(int scalar);
    Image operator*(float scalar);
    Image operator/(int scalar);
    Image operator/(float scalar);

    // transformasi log
    void transformasiLog(float scalar);
    void transformasiLogInv(float scalar);
    void transformasiPangkat(float scalar, float gamma);

    // contrast stretching
    void contrastStretching(int a, int b,float alpha, float beta, float gamma, int ya, int yb);
};
#endif