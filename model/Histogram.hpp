#ifndef Histogram_HPP
#define Histogram_HPP
#include "Image.hpp"
class Histogram
{
    public:
        float hist[256] = {0};
        float mean;
        float variansi;
        float standarDeviasi;
        bool isNormal;

        Histogram(Image& img, bool isNormal = false);
        Histogram(int size, unsigned char* data, bool isNormal = false);
};
#endif