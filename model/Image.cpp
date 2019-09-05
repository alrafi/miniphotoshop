#include "Image.hpp"

Image :: Image(int width, int height, bool isColor){
    this->width = width;
    this->height = height;
    this-isColor = isColor;
    size = width * height;

    if(isColor){
        createColorData();
    }else{
        createGreyData();
    }
}

Image :: ~Image(){
    if(colorData != NULL){
        deleteColorData();
    }
    if(greyData != NULL){
        deleteGreyData();
    }
}

void Image :: createColorData(){
    colorData = new Color [size];
}

void Image :: createGreyData(){
    greyData = new unsigned char [size];
}

void Image :: deleteColorData(){
    delete[] colorData;
}

void Image :: deleteGreyData(){
    delete[] greyData;
}

void Image :: setColorData(int x, int y, unsigned char R, unsigned char G, unsigned char B){
    colorData[(y*width) + x].setColor(R,G,B); 
}

void Image :: setGreyData(int x, int y, unsigned char grey){
    greyData[(y*width) + x] = grey;
}

Color Image :: getColorData(int x, int y){
    return colorData[(y * width) + x];
}

unsigned char Image :: getGreyData(int x, int y){
    return greyData[(y * width) + x];
}