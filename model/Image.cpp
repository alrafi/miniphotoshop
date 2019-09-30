#include "Image.hpp"
#include <iostream>
#include <math.h>
#include "Histogram.hpp"

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


Image Image :: operator+(Image const &img) {
    Image image;
    if ((this->size == img.size) && (this->isColor == img.isColor)) {
        image.setWidth(this->width);
        image.setHeight(this->height);
        image.updateSize();
        image.setColor(this->isColor);
        if (this->isColor) image.createColorData();
        else image.createGreyData();
        for (int i=0; i < this->size; i++) {
            if (this->isColor) {
                image.colorData[i] = this->colorData[i] + img.colorData[i];
            } else {
                int hasil = this->greyData[i] + img.greyData[i];
                image.greyData[i] = hasil > 255 ? 255 : hasil;
            }
        }
    }
    return image;
}

Image Image :: operator+(int scalar) {
    Image image;
    image.setWidth(this->width);
    image.setHeight(this->height);
    image.updateSize();
    image.setColor(this->isColor);
    if (this->isColor) image.createColorData();
    else image.createGreyData();
    for (int i=0; i < this->size; i++) {
        if (this->isColor) {
            image.colorData[i] = this->colorData[i] + scalar;
        } else {
            int hasil = this->greyData[i] + scalar;
            image.greyData[i] = hasil > 255 ? 255 : hasil;
        }
    }
    return image;
}

Image Image :: operator-(Image const &img) {
    Image image;
    if ((this->size == img.size) && (this->isColor == img.isColor)) {
        image.setWidth(this->width);
        image.setHeight(this->height);
        image.updateSize();
        image.setColor(this->isColor);
        if (this->isColor) image.createColorData();
        else image.createGreyData();
        for (int i=0; i < this->size; i++) {
            if (this->isColor) {
                image.colorData[i] = this->colorData[i] - img.colorData[i];
            } else {
                int hasil = this->greyData[i] - img.greyData[i];
                image.greyData[i] = hasil < 0 ? 0 : hasil;
            }
        }
    }
    return image;
}

Image Image :: operator-(int scalar){
    Image image;
    image.setWidth(this->width);
    image.setHeight(this->height);
    image.updateSize();
    image.setColor(this->isColor);
    if (this->isColor) image.createColorData();
    else image.createGreyData();
    for (int i=0; i < this->size; i++) {
        if (this->isColor) {
            image.colorData[i] = this->colorData[i] - scalar;
        } else {
            int hasil = this->greyData[i] - scalar;
            image.greyData[i] = hasil < 0 ? 0 : hasil;
        }
    }
    return image;
}

Image& Image::operator=(const Image &img) {
    if (this->isColor && this->colorData!=NULL) this->deleteColorData();
    else if (this->greyData!=NULL) this->deleteGreyData();
    this->width = img.width;
    this->height = img.height;
    this->isColor = img.isColor;
    this->size = img.size;
    if (this->isColor) this->createColorData();
    else this->createGreyData();
    for (int i = 0; i<this->size ;i++) {
        if (this->isColor) this->colorData[i] = img.colorData[i];
        else this->greyData[i] = img.greyData[i]; 
    }
    return *this;
}


Image Image::operator*(const Image &img){
    Image image;
    if ((this->isColor == img.isColor) && (this->width == img.height)) {
        image.width = img.width;
        image.height = this->height;
        image.updateSize();
        if (this->isColor) image.createColorData();
        else  image.createGreyData();
        for (int i=0; i<this->height; i++){
            for (int j=0; j<img.width; j++){
                int temp = 0;
                Color c;
                for (int k=0; k<this->width; k++) {
                    if (image.isColor) {
                        c = c + (this->colorData[(i * this->width) + k] * img.colorData[(k * img.width) + j]);
                    } else {
                        temp += (this->greyData[(i * this->width) + k] * img.greyData[(k * img.width) + j]);
                    }
                }
                if (image.isColor) {
                    image.colorData[(i * image.width) + j] = c;
                } else {
                    temp = temp<0 ? 0 : temp;
                    temp = temp>255 ? 255 : temp;
                    image.greyData[(i * image.width) + j] = temp;
                }
            }
        }
    }
    return image;
}
Image Image::operator*(int scalar){
    Image image;
    image.width = this->width;
    image.height = this->height;
    image.updateSize();
    image.isColor = this->isColor;
    if (this->isColor) image.createColorData();
    else  image.createGreyData();
    for (int i=0; i < image.size; i++) {
        if (image.isColor){
            image.colorData[i] = this->colorData[i] * scalar;
        } else {
            int temp = this->greyData[i] * scalar;
            temp = temp<0 ? 0 : temp;
            temp = temp>255 ? 255 : temp;
            image.greyData[i] = temp;
        }
    }
    return image;
}
Image Image::operator*(float scalar){
    Image image;
    image.width = this->width;
    image.height = this->height;
    image.updateSize();
    image.isColor = this->isColor;
    if (this->isColor) image.createColorData();
    else  image.createGreyData();
    for (int i=0; i < image.size; i++) {
        if (image.isColor){
            image.colorData[i] = this->colorData[i] * scalar;
        } else {
            int temp = round(this->greyData[i] * scalar);
            temp = temp<0 ? 0 : temp;
            temp = temp>255 ? 255 : temp;
            image.greyData[i] = temp;
        }
    }
    return image;
}
Image Image::operator/(int scalar){
    Image image;
    image.width = this->width;
    image.height = this->height;
    image.updateSize();
    image.isColor = this->isColor;
    if (this->isColor) image.createColorData();
    else  image.createGreyData();
    for (int i=0; i < image.size; i++) {
        if (image.isColor){
            image.colorData[i] = this->colorData[i] / scalar;
        } else {
            int temp = round(this->greyData[i] / scalar);
            temp = temp<0 ? 0 : temp;
            temp = temp>255 ? 255 : temp;
            image.greyData[i] = temp;
        }
    }
    return image;
}
Image Image::operator/(float scalar){
    Image image;
    image.width = this->width;
    image.height = this->height;
    image.updateSize();
    image.isColor = this->isColor;
    if (this->isColor) image.createColorData();
    else  image.createGreyData();
    for (int i=0; i < image.size; i++) {
        if (image.isColor){
            image.colorData[i] = this->colorData[i] / scalar;
        } else {
            int temp = round(this->greyData[i] / scalar);
            temp = temp<0 ? 0 : temp;
            temp = temp>255 ? 255 : temp;
            image.greyData[i] = temp;
        }
    }
    return image;
}

unsigned char* Image::getRedData(){
    unsigned char* data = new unsigned char[this->size];
    for (int i=0;i<this->size;i++) {
        data[i] = this->colorData[i].R;
    }
    return data;
}
unsigned char* Image::getGreenData(){
    unsigned char* data = new unsigned char[this->size];
    for (int i=0;i<this->size;i++) {
        data[i] = this->colorData[i].G;
    }
    return data;
}
unsigned char* Image::getBlueData(){
    unsigned char* data = new unsigned char[this->size];
    for (int i=0;i<this->size;i++) {
        data[i] = this->colorData[i].B;
    }
    return data;
}
void Image::transformasiLog(float scalar){
    for (int i=0;i<this->size;i++) {
        if (this->isColor) {
            int r = scalar * log (1 + this->colorData[i].R);
            int g = scalar * log (1 + this->colorData[i].G);
            int b = scalar * log (1 + this->colorData[i].B);
            this->colorData[i].R = r > 255 ? 255 : r;
            this->colorData[i].G = g > 255 ? 255 : g;
            this->colorData[i].B = b > 255 ? 255 : b;
        } else {
            int g = scalar * log(1 + this->greyData[i]);
            this->greyData[i] = g > 255 ? 255 : g;
        }
    }
}
void Image::transformasiLogInv(float scalar){
    for (int i=0;i<this->size;i++) {
        if (this->isColor) {
            int r = exp (1 + this->colorData[i].R) / scalar;
            int g = exp (1 + this->colorData[i].G) / scalar;
            int b = exp (1 + this->colorData[i].B) / scalar;
            this->colorData[i].R = r > 255 ? 255 : r;
            this->colorData[i].G = g > 255 ? 255 : g;
            this->colorData[i].B = b > 255 ? 255 : b;
        } else {
            int g = exp(1 + this->greyData[i]) / scalar;
            this->greyData[i] = g > 255 ? 255 : g;
        }
    }
}

void Image::transformasiPangkat(float scalar, float gamma){
    for (int i=0;i<this->size;i++) {
        if (this->isColor) {
            int r = scalar * pow (this->colorData[i].R, 1/gamma);
            int g = scalar * pow (this->colorData[i].G, 1/gamma);
            int b = scalar * pow (this->colorData[i].B, 1/gamma);
            this->colorData[i].R = r > 255 ? 255 : r;
            this->colorData[i].G = g > 255 ? 255 : g;
            this->colorData[i].B = b > 255 ? 255 : b;
        } else {
            int g = scalar * pow (this->greyData[i], 1/gamma);
            this->greyData[i] = g > 255 ? 255 : g;
        }
    }
}

void Image::contrastStretching(int a, int b,float alpha, float beta, float gamma, int ya, int yb){
    if (this->isColor) {
        for (int i=0; i<this->size; i++) {
            int R = this->colorData[i].R; 
            int G = this->colorData[i].G;
            int B = this->colorData[i].B;
            // red
            if (R < a) this->colorData[i].R = (alpha * R) > 255 ? 255:alpha*R;
            else if (R >=b) this->colorData[i].R = (gamma * (R - b) + yb) > 255 ? 255:(gamma * (R - b) + yb);
            else this->colorData[i].R = (beta * (R - a) + ya) > 255 ? 255:(beta * (R - a) + ya);
            // green
            if (G < a) this->colorData[i].G = (alpha * G) > 255 ? 255:(alpha * G);
            else if (G >=b) this->colorData[i].G = (gamma * (G - b) + yb) > 255 ? 255:(gamma * (G - b) + yb);
            else this->colorData[i].G = (beta * (G - a) + ya) > 255 ? 255:(beta * (G - a) + ya);
            // blue
            if (B < a) this->colorData[i].B = (alpha * B) > 255 ? 255:(alpha * B);
            else if (B >=b) this->colorData[i].B = (gamma * (B - b) + yb) > 255 ? 255:(gamma * (B - b) + yb);
            else this->colorData[i].B = (beta * (B - a) + ya) > 255 ? 255:(beta * (B - a) + ya);
        }
    } else {
        for (int i=0; i<this->size; i++) {
            int val = this->greyData[i];
            if (val < a) this->greyData[i] = (alpha * val) > 255 ? 255:(alpha * val);
            else if (val >=b) this->greyData[i] = (gamma * (val - b) + yb) > 255 ? 255:(gamma * (val - b) + yb);
            else this->greyData[i] = (beta * (val - a) + ya) > 255 ? 255:(beta * (val - a) + ya);
        }
    }
}