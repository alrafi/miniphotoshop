#ifndef HistogramColor_HPP
#define HistogramColor_HPP
#include "Image.hpp"
#include "Histogram.hpp"
class HistogramColor
{
    public: 
        Histogram* r;
        Histogram* g;
        Histogram* b;

        HistogramColor(Image& img, bool isNormal=false);
        ~HistogramColor();
};
#endif