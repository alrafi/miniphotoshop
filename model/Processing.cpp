#include "Processing.hpp"
#include "Histogram.hpp"
#include <iostream>
#include <cmath>

using namespace std;

// Perataan Histogram
void Processing::perataanHistogram(Image &image)
{
    float sum;
    int HistEq[256];
    Histogram newHist(image, true);
    for (int i = 0; i < 256; i++)
    {
        sum = 0.0;
        for (int j = 0; j <= i; j++)
        {
            sum += newHist.hist[j];
        }
        HistEq[i] = floor(255 * sum);
    }
    cout << "oke" << endl;
    for (int i = 0; i < image.size; i++)
    {
        image.setGreyDataByIndex(i, HistEq[image.greyData[i]]);
        // cout << "size-" << i << endl;
    }
    cout << "siap" << endl;
};
// end of Perataan Histogram