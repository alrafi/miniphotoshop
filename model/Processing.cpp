#include "Processing.hpp"
#include "Histogram.hpp"
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

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

// hitungMedian
int Processing::hitungMedian(int *arr, int size)
{
    sort(arr, arr + size);
    if (size % 2 == 0)
    {
        int idx1 = size / 2;
        int idx2 = size / 2 + 1;
        return (arr[idx1] + arr[idx2]) / 2;
    }
    else
    {
        return arr[(size - 1) / 2 + 1];
    }
}

// penapis median
void Processing::penapisMedian(Image &image)
{
    Image imgtmp; // acuan
    imgtmp = image;

    if (image.isColor)
    {
        int filter_median_r[9];
        int filter_median_g[9];
        int filter_median_b[9];
        for (int i = 0; i < image.height - 2; i++)
        {
            for (int j = 0; j < image.width - 2; j++)
            {
                int idx = 0;
                for (int k = i; k < i + 3; k++)
                { // baris filter
                    for (int l = j; l < j + 3; l++)
                    { // kolom filter
                        filter_median_r[idx] = imgtmp.getColorData(l, k).R;
                        filter_median_g[idx] = imgtmp.getColorData(l, k).G;
                        filter_median_b[idx] = imgtmp.getColorData(l, k).B;
                        idx++;
                    }
                }
                // set data image [i+1, j+1] with value of median
                int median_value_r = Processing::hitungMedian(filter_median_r, 9);
                int median_value_g = Processing::hitungMedian(filter_median_g, 9);
                int median_value_b = Processing::hitungMedian(filter_median_b, 9);
                // if (i == 2 && j == 2)
                // {
                // sort(filter_median_r, filter_median_r + 9);
                // sort(filter_median_g, filter_median_g + 9);
                // sort(filter_median_b, filter_median_b + 9);
                // for (int ii = 0; ii < 9; ii++)
                // {
                //     cout << filter_median_r[ii] << " ";
                // }
                // cout << median_value_r << endl;
                // }
                image.setColorData(j + 1, i + 1, median_value_r, median_value_g, median_value_b);
            }
        }
    }
    else
    {
        int filter_median[9];
        for (int i = 0; i < image.height - 2; i++)
        {
            for (int j = 0; j < image.width - 2; j++)
            {
                int idx = 0;
                for (int k = i; k < i + 3; k++)
                { // baris filter
                    for (int l = j; l < j + 3; l++)
                    { // kolom filter
                        filter_median[idx] = imgtmp.getGreyData(l, k);
                        idx++;
                    }
                }
                // set data image [i+1, j+1] with value of median
                int median_value = Processing::hitungMedian(filter_median, 9);
                // if (i == 2 && j == 2)
                // {
                //     sort(filter_median, filter_median + 9);
                //     for (int ii = 0; ii < 9; ii++)
                //     {
                //         cout << filter_median[ii] << " ";
                //     }
                //     cout << median_value << endl;
                // }
                image.setGreyData(j + 1, i + 1, median_value);
            }
        }
    }
}
// end of penapis median