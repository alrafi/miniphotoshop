#include "HistogramColor.hpp"
#include "Histogram.hpp"
#include <math.h>
#include <cstddef>
HistogramColor::HistogramColor(Image &img, bool isNormal)
{
    r = new Histogram(img.size, img.getRedData(), isNormal);
    g = new Histogram(img.size, img.getGreenData(), isNormal);
    b = new Histogram(img.size, img.getBlueData(), isNormal);
}
HistogramColor::~HistogramColor()
{
    if (r != NULL)
        delete[] r;
    if (g != NULL)
        delete[] g;
    if (b != NULL)
        delete[] b;
}