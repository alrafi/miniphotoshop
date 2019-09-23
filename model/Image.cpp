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

void Image :: citraNegativeGrayscale(){
    if (greyData != NULL){
        for(int i =0; i<size; i++){
            greyData[i] = 255 - greyData[i];
        }
    }
}

void Image :: citraNegativeColor(){
    if (colorData != NULL){
        for(int i = 0; i<size; i++){
            colorData[i].R = 255 - colorData[i].R;
            colorData[i].G = 255 - colorData[i].G;
            colorData[i].B = 255 - colorData[i].B;
        }
    }
}

void Image :: brightnessGrayscale(int b){
    if(greyData != NULL){
        for(int i = 0; i<size; i++){
            if(greyData[i]+b > 255){
                greyData[i] = 255;
            }else if (greyData[i]+b<0){
                greyData[i] = 0;
            }else{
                greyData[i] = greyData[i] + b;
            }
        }
    }
}

void Image :: brightnessColorscale(int b){
    if(colorData != NULL){
        for(int i = 0; i<size; i++){
            if(colorData[i].R +b > 255){
                colorData[i].R = 255;
            }else if (colorData[i].R+b<0){
                colorData[i].R = 0;
            }else{
                colorData[i].R = colorData[i].R + b;
            }

            if(colorData[i].G +b > 255){
                colorData[i].G = 255;
            }else if (colorData[i].G+b<0){
                colorData[i].G = 0;
            }else{
                colorData[i].G = colorData[i].G + b;
            }

            if(colorData[i].B +b > 255){
                colorData[i].B = 255;
            }else if (colorData[i].B+b<0){
                colorData[i].B = 0;
            }else{
                colorData[i].B = colorData[i].B + b;
            }
        }
    }
}

void Image :: colorToGrayscale(){
    if(colorData != NULL){
        createGreyData();
        for(int i=0; i<size; i++){
            int gray = (0.3* (int) colorData[i].R + 0.59 * (int)colorData[i].G + 0.11 * (int)colorData[i].B);
            greyData[i] = gray;
        }
    }
}

Image Image :: operator&(Image image){
    Image newImage;
    if ((this->isColor == true) && (image.isColor == true)){
        if(this->width == image.width && this->height == image.height){
            newImage.setWidth(this->width);
            newImage.setHeight(this->height);
            newImage.updateSize();
            newImage.createColorData();
            for(int i=0; i < this->size; i++){
                unsigned char r = this->getColorDataByIndex(i).R & image.getColorDataByIndex(i).R;
                unsigned char g = this->getColorDataByIndex(i).G & image.getColorDataByIndex(i).G;
                unsigned char b = this->getColorDataByIndex(i).B & image.getColorDataByIndex(i).B;
                newImage.setColorDataByIndex(i, r, g, b);
            }
        }
    }else if((this->isColor == false) && (image.isColor == false)){
        if(this->width == image.width && this->height == image.height){
            newImage.setWidth(this->width);
            newImage.setHeight(this->height);
            newImage.updateSize();
            newImage.createGreyData();
            for(int i=0; i < this->size; i++){
                unsigned char c = this->getGreyDataByIndex(i) & image.getGreyDataByIndex(i);
                newImage.setGreyDataByIndex(i, c);
            }
        }
    }
    return newImage;
}

Image Image :: operator|(Image image){
    Image newImage;
    if ((this->isColor == true) && (image.isColor == true)){
        if(this->width == image.width && this->height == image.height){
            newImage.setWidth(this->width);
            newImage.setHeight(this->height);
            newImage.updateSize();
            newImage.createColorData();
            for(int i=0; i < this->size; i++){
                unsigned char r = this->getColorDataByIndex(i).R | image.getColorDataByIndex(i).R;
                unsigned char g = this->getColorDataByIndex(i).G | image.getColorDataByIndex(i).G;
                unsigned char b = this->getColorDataByIndex(i).B | image.getColorDataByIndex(i).B;
                newImage.setColorDataByIndex(i, r, g, b);
            }
        }
    }else if((this->isColor == false) && (image.isColor == false)){
        if(this->width == image.width && this->height == image.height){
            newImage.setWidth(this->width);
            newImage.setHeight(this->height);
            newImage.updateSize();
            newImage.createGreyData();
            for(int i=0; i < this->size; i++){
                unsigned char c = this->getGreyDataByIndex(i) | image.getGreyDataByIndex(i);
                newImage.setGreyDataByIndex(i, c);
            }
        }
    }
    return newImage;
}

Image& Image :: operator~(){
    if (this->isColor == true){
        for(int i = 0; i<this->size; i++){
            unsigned char r = ~this->getColorDataByIndex(i).R; 
            unsigned char g = ~this->getColorDataByIndex(i).G;
            unsigned char b = ~this->getColorDataByIndex(i).B;
            this->setColorDataByIndex(i,r,g,b);
        }
    }else{
        for(int i = 0; i<this->size; i++){
            unsigned char c = ~this->getGreyDataByIndex(i);
            this->setGreyDataByIndex(i,c);
        }
    }
    return *this;
}

Image Image :: rotasi90CW(){
    Image temp;
    if(this->isColor == true){
        temp.setWidth(this->height);
        temp.setHeight(this->width);
        temp.updateSize();
        temp.createColorData();
        int index = 0;
        for(int i=this->height-1; i>=0; i--){
            for(int j=0; j<this->width; j++){
                unsigned char r = this->getColorDataByIndex(index).R;
                unsigned char g = this->getColorDataByIndex(index).G;
                unsigned char b = this->getColorDataByIndex(index).B;
                temp.setColorData(j,i,r,g,b);
                index++;
            }
        }
    }else{
        temp.setWidth(this->height);
        temp.setHeight(this->width);
        temp.updateSize();
        temp.createGreyData();
        int index = 0;
        for(int i=this->height-1; i>=0; i--){
            for(int j=0; j<this->width; j++){
                unsigned char c = this->getGreyDataByIndex(index);
                temp.setGreyData(j,i,c);
                index++;
            }
        }
    }
    return temp;
}

Image Image :: rotasi90CCW(){
    Image temp;
    if(this->isColor == true){
        temp.setWidth(this->height);
        temp.setHeight(this->width);
        temp.updateSize();
        temp.createColorData();
        int index = 0;
        for(int i=0; i<this->height; i++){
            for(int j=this->width-1; j>=0; j--){
                unsigned char r = this->getColorDataByIndex(index).R;
                unsigned char g = this->getColorDataByIndex(index).G;
                unsigned char b = this->getColorDataByIndex(index).B;
                temp.setColorData(j,i,r,g,b);
                index++;
            }
        }
    }else{
        temp.setWidth(this->height);
        temp.setHeight(this->width);
        temp.updateSize();
        temp.createGreyData();
        int index = 0;
        for(int i=0; i<this->height; i++){
            for(int j=this->width-1; j>=0; j--){
                unsigned char c = this->getGreyDataByIndex(index);
                temp.setGreyData(j,i,c);
                index++;
            }
        }
    }
    return temp;
}

Image Image :: rotasi180(){
    Image temp;
    if(this->isColor == true){
        temp.setWidth(this->width);
        temp.setHeight(this->height);
        temp.updateSize();
        temp.createColorData();
        int index = 0;
        for(int i=this->height-1; i>=0; i--){
            for(int j=this->width-1; j>=0; j--){
                unsigned char r = this->getColorDataByIndex(index).R;
                unsigned char g = this->getColorDataByIndex(index).G;
                unsigned char b = this->getColorDataByIndex(index).B;
                temp.setColorData(j,i,r,g,b);
                index++;
            }
        }
    }else{
        temp.setWidth(this->width);
        temp.setHeight(this->height);
        temp.updateSize();
        temp.createGreyData();
        int index = 0;
        for(int i=this->height-1; i>=0; i--){
            for(int j=this->width-1; j>=0; j--){
                unsigned char c = this->getGreyDataByIndex(index);
                temp.setGreyData(j,i,c);
                index++;
            }
        }
    }
    return temp;
}

Image Image :: flipping(int type){
    Image temp;
    //horizontal
    if (type == 1){
        if(this->isColor == true){
            temp.setWidth(this->width);
            temp.setHeight(this->height);
            temp.updateSize();
            temp.createColorData();
            int index = 0;
            for(int i = this->height-1; i>=0;i--){
                for(int j = 0; j<this->width; j++){
                    unsigned char r = this->getColorDataByIndex(index).R;
                    unsigned char g = this->getColorDataByIndex(index).G;
                    unsigned char b = this->getColorDataByIndex(index).B;
                    temp.setColorData(i,j,r,g,b);
                    index++;
                }
            }
        } else {
            temp.setWidth(this->width);
            temp.setHeight(this->height);
            temp.updateSize();
            temp.createGreyData();
            int index = 0;
            for(int i = this->height-1; i>=0;i--){
                for(int j = 0; j<this->width; j++){
                    unsigned char c = this->getGreyDataByIndex(index);
                    temp.setGreyData(i,j,c);
                    index++;
                }
            }
        }
    }
    //vertical
    else if (type == 0){
        if(this->isColor == true){
            temp.setWidth(this->width);
            temp.setHeight(this->height);
            temp.updateSize();
            temp.createColorData();
            int index = 0;
            for(int i = 0; i<this->height;i++){
                for(int j = this->width-1; j>=0; j--){
                    unsigned char r = this->getColorDataByIndex(index).R;
                    unsigned char g = this->getColorDataByIndex(index).G;
                    unsigned char b = this->getColorDataByIndex(index).B;
                    temp.setColorData(i,j,r,g,b);
                    index++;
                }
            }
        } else {
            temp.setWidth(this->width);
            temp.setHeight(this->height);
            temp.updateSize();
            temp.createGreyData();
            int index = 0;
            for(int i = 0; i<this->height;i++){
                for(int j = this->width-1; j>=0; j--){
                    unsigned char c = this->getGreyDataByIndex(index);
                    temp.setGreyData(i,j,c);
                    index++;
                }
            }
        }
    }
    return temp;
}