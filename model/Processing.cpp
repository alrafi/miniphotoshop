#include "Processing.hpp"
#include "Histogram.hpp"
#include "HistogramColor.hpp"
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

// Perataan Histogram
void Processing::perataanHistogram(Image &image)
{
    float sum_r = 0;
    float sum_g = 0;
    float sum_b = 0;
    int HistEq_r[256];
    int HistEq_g[256];
    int HistEq_b[256];
    // cout << "oke" << endl;
    if (image.isColor)
    {
        HistogramColor colorHist(image, true);
        for (int i = 0; i < 256; i++)
        {
            sum_r = sum_g = sum_b = 0.0;
            for (int j = 0; j <= i; j++)
            {
                sum_r += colorHist.r->hist[j];
                sum_g += colorHist.g->hist[j];
                sum_b += colorHist.b->hist[j];
            }
            HistEq_r[i] = floor(255 * sum_r);
            HistEq_g[i] = floor(255 * sum_g);
            HistEq_b[i] = floor(255 * sum_b);
        }
        for (int i = 0; i < image.size; i++)
        {
            unsigned char r = image.getColorDataByIndex(i).R;
            unsigned char g = image.getColorDataByIndex(i).G;
            unsigned char b = image.getColorDataByIndex(i).B;
            image.setColorDataByIndex(i, HistEq_r[r], HistEq_g[g], HistEq_b[b]);
        }
    }
    else
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
        for (int i = 0; i < image.size; i++)
        {
            image.setGreyDataByIndex(i, HistEq[image.greyData[i]]);
        }
    }
}
// end of Perataan Histogram

// Spesifikasi histogram for color image
void Processing::spesifikasiHistogram(Image &image, HistogramColor &spec)
{
    float sum_r, sum_g, sum_b;
    int minj_r, minj_g, minj_b;
    int minval_r, minval_g, minval_b;
    int HistEq_r[256], HistEq_g[256], HistEq_b[256];
    int SpecEq_r[256], SpecEq_g[256], SpecEq_b[256];
    int InvHist_r[256], InvHist_g[256], InvHist_b[256];

    HistogramColor colorHist(image, true);
    for (int i = 0; i < 256; i++)
    {
        sum_r = 0.0;
        sum_g = 0.0;
        sum_b = 0.0;
        for (int j = 0; j <= i; j++)
        {
            sum_r += colorHist.r->hist[j];
            sum_g += colorHist.g->hist[j];
            sum_b += colorHist.b->hist[j];
        }
        HistEq_r[i] = floor(255 * sum_r);
        HistEq_g[i] = floor(255 * sum_g);
        HistEq_b[i] = floor(255 * sum_b);
    }

    // perataan histogram untuk citra spec
    for (int i = 0; i < 256; i++)
    {
        sum_r = 0.0;
        sum_g = 0.0;
        sum_b = 0.0;
        for (int j = 0; j <= i; j++)
        {
            sum_r += spec.r->hist[j];
            sum_g += spec.g->hist[j];
            sum_b += spec.b->hist[j];
        }
        SpecEq_r[i] = floor(255 * sum_r);
        SpecEq_g[i] = floor(255 * sum_g);
        SpecEq_b[i] = floor(255 * sum_b);
    }

    // melakukan tranformasi balikan
    for (int i = 0; i < image.width; i++)
    {
        minval_r = abs(HistEq_r[i] - SpecEq_r[0]);
        minval_g = abs(HistEq_g[i] - SpecEq_g[0]);
        minval_b = abs(HistEq_b[i] - SpecEq_b[0]);
        minj_r = 0;
        minj_g = 0;
        minj_b = 0;
        for (int j = 0; j < 256; j++)
        {
            if (abs(HistEq_r[i] - SpecEq_r[j]) < minval_r)
            {
                minval_r = abs(HistEq_r[i] - SpecEq_r[j]);
                minj_r = j;
            }
            if (abs(HistEq_g[i] - SpecEq_g[j]) < minval_g)
            {
                minval_g = abs(HistEq_g[i] - SpecEq_g[j]);
                minj_g = j;
            }
            if (abs(HistEq_b[i] - SpecEq_b[j]) < minval_b)
            {
                minval_b = abs(HistEq_b[i] - SpecEq_b[j]);
                minj_b = j;
            }
        }
        InvHist_r[i] = minj_r;
        InvHist_g[i] = minj_g;
        InvHist_b[i] = minj_b;
    }

    // update citra setelah pembentukan histogram
    for (int i = 0; i < image.size; i++)
    {
        unsigned char r = image.getColorDataByIndex(i).R;
        unsigned char g = image.getColorDataByIndex(i).G;
        unsigned char b = image.getColorDataByIndex(i).B;
        image.setColorDataByIndex(i, InvHist_r[r], InvHist_g[g], InvHist_b[b]);
    }
}

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