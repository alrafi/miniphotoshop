#include "Spektrum.hpp"
#include <math.h>
#include <iostream>

Spektrum::Spektrum(const Image &img){
    double tetha;
    this->size = img.size;
    this->height = img.height;
    this->width = img.width;
    this->real = new double[this->size];
    this->imag = new double[this->size];
    for (int i=0; i<this->size; i++) { 
        real[i]=0;
        imag[i]=0;
    }
    for (int i=0; i<this->size; i++){
         for (int j=0; j<this->size-1; j++){
            tetha= i*2*3.14*j/(double)this->size;
            this->real[i]=this->real[i]+(img.greyData[j]*cos(tetha))/(double)this->size;
            this->imag[i]=this->imag[i]-(img.greyData[j]*sin(tetha))/(double)this->size;
         }
    }
}

Spektrum::~Spektrum(){
    delete [] this->real;
    delete [] this->imag;
}

Image& Spektrum::getSpektrum(){
    Image* img = new Image;
    img->height = this->height;
    img->width = this->width;
    img->size = this->size;
    img->isColor = false;
    img->createGreyData();
    double temp;
    for (int i=0; i<this->size; i++){
        temp = sqrt(pow(this->real[i],2)+pow(this->imag[i],2));
        temp = temp > 255 ? 255 : temp;
        img->greyData[(i + this->size/2) % this->size] = temp < 0 ? 0: temp;
    }
    img->transformasiLog(100);
    return *img;
}

Image& Spektrum::balikan(){
    // transformasi balikan
    double tetha, epsilon = 1E-12;
    double *tempr, *tempi;
    tempr = new double[this->size];
    tempi = new double[this->size]; 
    for (int i=0; i<this->size; i++){ 
        tempr[i]=0;
        tempi[i]=0;
    }
    for (int i=0; i<this->size; i++){ 
        for (int j=0; j<this->size-1; j++) {
            tetha= i*2*3.14*j/(double)this->size;
            tempr[i]=tempr[i]+(this->real[j]*cos(tetha) - this->imag[j]*sin(tetha));
            tempi[i]=tempi[i]+(this->imag[j]*cos(tetha) + this->real[j]*sin(tetha));
        }
        if (tempi[i] < epsilon) tempi[i]=0;
    }
    // create image
    Image* img = new Image;
    img->height = this->height;
    img->width = this->width;
    img->size = this->size;
    img->isColor = false;
    img->createGreyData();
    double temp;
    for (int i=0; i<this->size; i++){
        temp = sqrt(pow(tempr[i],2)+pow(tempi[i],2));
        temp = temp > 255 ? 255 : temp;
        img->greyData[i] = temp < 0 ? 0: temp;
    }
    return *img;
}

void Spektrum::show(){
    std::cout << "height: " << this->height << std::endl;
    std::cout << "width: " << this->width << std::endl;
    std::cout << "size: " << this->size << std::endl;
    std::cout << "Data:" << std::endl;
    for (int i=0; i<10; i++){
        std::cout << "{" << this->real[i] << "," << this->imag[i] << "}" << std::endl; 
    }
}