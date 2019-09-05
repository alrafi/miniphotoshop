#include "Image.hpp"
#include <iostream>

using namespace std;
Image :: Image(){
    this->width = 0;
    this->height = 0;
    this->isColor = false;
    size = width * height;
}

Image :: Image(int width, int height, bool isColor){
    this->width = width;
    this->height = height;
    this->isColor = isColor;
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

void Image :: setWidth(int width){
    this->width = width;
}

void Image :: setHeight(int heigth){
    this->height = heigth;
}

void Image :: setColor(bool isColor){
    this->isColor = isColor;
}

void Image :: updateSize(){
    size = width * height;
}

void Image :: setColorData(int x, int y, unsigned char R, unsigned char G, unsigned char B){
    colorData[(y*width) + x].setColor(R,G,B); 
}

void Image :: setGreyData(int x, int y, unsigned char grey){
    greyData[(y*width) + x] = grey;
}

void Image :: setColorDataByIndex(int index, unsigned char R, unsigned char G, unsigned char B){
    colorData[index].setColor(R,G,B);
}
    
    
void Image :: setGreyDataByIndex(int index, unsigned char grey){
    greyData[index] = grey;
}
Color Image :: getColorDataByIndex(int index){
    return colorData[index];
}

unsigned char Image :: getGreyDataByIndex(int index){
    return greyData[index];
}

Color Image :: getColorData(int x, int y){
    return colorData[(y * width) + x];
}

unsigned char Image :: getGreyData(int x, int y){
    return greyData[(y * width) + x];
}