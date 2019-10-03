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
}
// end of Perataan Histogram

// Spesifikasi histogram
void Processing::spesifikasiHistogram(Image &image, Histogram &spec)
{
    float sum;
    int minj, minval, HistEq[256], SpecEq[256], InvHist[256];
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

    // perataan histogram untuk citra spec
    for (int i = 0; i < 256; i++)
    {
        sum = 0.0;
        for (int j = 0; j <= i; j++)
        {
            sum += spec.hist[j];
        }
        SpecEq[i] = floor(255 * sum);
    }

    // melakukan tranformasi balikan
    for (int i = 0; i < image.width; i++)
    {
        minval = abs(HistEq[i] - SpecEq[0]);
        minj = 0;
        for (int j = 0; j < 256; j++)
        {
            if (abs(HistEq[i] - SpecEq[j]) < minval)
            {
                minval = abs(HistEq[i] - SpecEq[j]);
                minj = j;
            }
        }
        InvHist[i] = minj;
    }

    // update citra setelah pembentukan histogram
    for (int i = 0; i < image.size; i++)
    {
        image.setGreyDataByIndex(i, InvHist[image.greyData[i]]);
    }
}
// end of Spesifikasi Histogram