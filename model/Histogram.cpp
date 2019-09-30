#include "Histogram.hpp"
#include <math.h>

Histogram::Histogram(Image& img, bool isNormal){
    this->isNormal = isNormal;
    // compute mean + histogram
    long sum=0;
    for (int i=0; i<img.size; i++) {
        this->hist[img.getGreyDataByIndex(i)]+=1;
        sum+=img.getGreyDataByIndex(i);
    }
    this->mean = sum / img.size;
    
    // create normal histogram
    if (isNormal) {
        for (int i=0; i<256; i++) {
            this->hist[i] /= img.size;
        }
    }

    // compute variance
    double temp = 0;
    for (int i=0; i<img.size; i++) {
        temp+=pow(img.getGreyDataByIndex(i) - this->mean,2);
    }
    this->variansi = temp / img.size;
    this->standarDeviasi = sqrt(this->variansi);
}

Histogram::Histogram(int size, unsigned char* data, bool isNormal) {
    this->isNormal = isNormal;
    // compute mean + histogram
    long sum=0;
    for (int i=0; i<size; i++) {
        this->hist[data[i]]+=1;
        sum+=data[i]; 
    }
    this->mean = sum / size;
    
    // create normal histogram
    if (isNormal) {
        for (int i=0; i<256; i++) {
            this->hist[i] /= size;
        }
    }

    // compute variance
    double temp = 0;
    for (int i=0; i<size; i++) {
        temp+=pow(data[i] - this->mean,2);
    }
    this->variansi = temp / size;
    this->standarDeviasi = sqrt(this->variansi);
}