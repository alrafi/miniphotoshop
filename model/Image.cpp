#include "Image.hpp"
#include <iostream>
#include <math.h>
#include "Histogram.hpp"
#include <vector>
#include <cstdlib>

using namespace std;
Image ::Image()
{
    this->width = 0;
    this->height = 0;
    this->isColor = false;
    size = width * height;
}

Image ::Image(int width, int height, bool isColor)
{
    this->width = width;
    this->height = height;
    this->isColor = isColor;
    size = width * height;

    if (isColor)
    {
        createColorData();
    }
    else
    {
        createGreyData();
    }
}

Image ::~Image()
{
    if (colorData != NULL)
    {
        deleteColorData();
    }
    if (greyData != NULL)
    {
        deleteGreyData();
    }
}

void Image ::createColorData()
{
    colorData = new Color[size];
}

void Image ::createGreyData()
{
    greyData = new unsigned char[size];
}

void Image ::deleteColorData()
{
    delete[] colorData;
}

void Image ::deleteGreyData()
{
    delete[] greyData;
}

void Image ::setWidth(int width)
{
    this->width = width;
}

void Image ::setHeight(int heigth)
{
    this->height = heigth;
}

void Image ::setColor(bool isColor)
{
    this->isColor = isColor;
}

void Image ::updateSize()
{
    size = width * height;
}

void Image ::setColorData(int x, int y, unsigned char R, unsigned char G, unsigned char B)
{
    colorData[(y * width) + x].setColor(R, G, B);
}

void Image ::setGreyData(int x, int y, unsigned char grey)
{
    greyData[(y * width) + x] = grey;
}

void Image ::setColorDataByIndex(int index, unsigned char R, unsigned char G, unsigned char B)
{
    colorData[index].setColor(R, G, B);
}

void Image ::setGreyDataByIndex(int index, unsigned char grey)
{
    greyData[index] = grey;
}
Color Image ::getColorDataByIndex(int index)
{
    return colorData[index];
}

unsigned char Image ::getGreyDataByIndex(int index)
{
    return greyData[index];
}

Color Image ::getColorData(int x, int y)
{
    return colorData[(y * width) + x];
}

unsigned char Image ::getGreyData(int x, int y)
{
    return greyData[(y * width) + x];
}

Image Image ::operator+(Image const &img)
{
    Image image;
    if ((this->size == img.size) && (this->isColor == img.isColor))
    {
        image.setWidth(this->width);
        image.setHeight(this->height);
        image.updateSize();
        image.setColor(this->isColor);
        if (this->isColor)
            image.createColorData();
        else
            image.createGreyData();
        for (int i = 0; i < this->size; i++)
        {
            if (this->isColor)
            {
                image.colorData[i] = this->colorData[i] + img.colorData[i];
            }
            else
            {
                int hasil = this->greyData[i] + img.greyData[i];
                image.greyData[i] = hasil > 255 ? 255 : hasil;
            }
        }
    }
    return image;
}

Image Image ::operator+(int scalar)
{
    Image image;
    image.setWidth(this->width);
    image.setHeight(this->height);
    image.updateSize();
    image.setColor(this->isColor);
    if (this->isColor)
        image.createColorData();
    else
        image.createGreyData();
    for (int i = 0; i < this->size; i++)
    {
        if (this->isColor)
        {
            image.colorData[i] = this->colorData[i] + scalar;
        }
        else
        {
            int hasil = this->greyData[i] + scalar;
            image.greyData[i] = hasil > 255 ? 255 : hasil;
        }
    }
    return image;
}

Image Image ::operator-(Image const &img)
{
    Image image;
    if ((this->size == img.size) && (this->isColor == img.isColor))
    {
        image.setWidth(this->width);
        image.setHeight(this->height);
        image.updateSize();
        image.setColor(this->isColor);
        if (this->isColor)
            image.createColorData();
        else
            image.createGreyData();
        for (int i = 0; i < this->size; i++)
        {
            if (this->isColor)
            {
                image.colorData[i] = this->colorData[i] - img.colorData[i];
            }
            else
            {
                int hasil = this->greyData[i] - img.greyData[i];
                image.greyData[i] = hasil < 0 ? 0 : hasil;
            }
        }
    }
    return image;
}

Image Image ::operator-(int scalar)
{
    Image image;
    image.setWidth(this->width);
    image.setHeight(this->height);
    image.updateSize();
    image.setColor(this->isColor);
    if (this->isColor)
        image.createColorData();
    else
        image.createGreyData();
    for (int i = 0; i < this->size; i++)
    {
        if (this->isColor)
        {
            image.colorData[i] = this->colorData[i] - scalar;
        }
        else
        {
            int hasil = this->greyData[i] - scalar;
            image.greyData[i] = hasil < 0 ? 0 : hasil;
        }
    }
    return image;
}

Image &Image::operator=(const Image &img)
{
    if (this->isColor && this->colorData != NULL)
        this->deleteColorData();
    else if (this->greyData != NULL)
        this->deleteGreyData();
    this->width = img.width;
    this->height = img.height;
    this->isColor = img.isColor;
    this->size = img.size;
    if (this->isColor)
        this->createColorData();
    else
        this->createGreyData();
    for (int i = 0; i < this->size; i++)
    {
        if (this->isColor)
            this->colorData[i] = img.colorData[i];
        else
            this->greyData[i] = img.greyData[i];
    }
    return *this;
}

Image Image::operator*(const Image &img)
{
    Image image;
    if ((this->isColor == img.isColor) && (this->width == img.height))
    {
        image.width = img.width;
        image.height = this->height;
        image.updateSize();
        if (this->isColor)
            image.createColorData();
        else
            image.createGreyData();
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < img.width; j++)
            {
                int temp = 0;
                Color c;
                for (int k = 0; k < this->width; k++)
                {
                    if (image.isColor)
                    {
                        c = c + (this->colorData[(i * this->width) + k] * img.colorData[(k * img.width) + j]);
                    }
                    else
                    {
                        temp += (this->greyData[(i * this->width) + k] * img.greyData[(k * img.width) + j]);
                    }
                }
                if (image.isColor)
                {
                    image.colorData[(i * image.width) + j] = c;
                }
                else
                {
                    temp = temp < 0 ? 0 : temp;
                    temp = temp > 255 ? 255 : temp;
                    image.greyData[(i * image.width) + j] = temp;
                }
            }
        }
    }
    return image;
}
Image Image::operator*(int scalar)
{
    Image image;
    image.width = this->width;
    image.height = this->height;
    image.updateSize();
    image.isColor = this->isColor;
    if (this->isColor)
        image.createColorData();
    else
        image.createGreyData();
    for (int i = 0; i < image.size; i++)
    {
        if (image.isColor)
        {
            image.colorData[i] = this->colorData[i] * scalar;
        }
        else
        {
            int temp = this->greyData[i] * scalar;
            temp = temp < 0 ? 0 : temp;
            temp = temp > 255 ? 255 : temp;
            image.greyData[i] = temp;
        }
    }
    return image;
}
Image Image::operator*(float scalar)
{
    Image image;
    image.width = this->width;
    image.height = this->height;
    image.updateSize();
    image.isColor = this->isColor;
    if (this->isColor)
        image.createColorData();
    else
        image.createGreyData();
    for (int i = 0; i < image.size; i++)
    {
        if (image.isColor)
        {
            image.colorData[i] = this->colorData[i] * scalar;
        }
        else
        {
            int temp = round(this->greyData[i] * scalar);
            temp = temp < 0 ? 0 : temp;
            temp = temp > 255 ? 255 : temp;
            image.greyData[i] = temp;
        }
    }
    return image;
}
Image Image::operator/(int scalar)
{
    Image image;
    image.width = this->width;
    image.height = this->height;
    image.updateSize();
    image.isColor = this->isColor;
    if (this->isColor)
        image.createColorData();
    else
        image.createGreyData();
    for (int i = 0; i < image.size; i++)
    {
        if (image.isColor)
        {
            image.colorData[i] = this->colorData[i] / scalar;
        }
        else
        {
            int temp = round(this->greyData[i] / scalar);
            temp = temp < 0 ? 0 : temp;
            temp = temp > 255 ? 255 : temp;
            image.greyData[i] = temp;
        }
    }
    return image;
}
Image Image::operator/(float scalar)
{
    Image image;
    image.width = this->width;
    image.height = this->height;
    image.updateSize();
    image.isColor = this->isColor;
    if (this->isColor)
        image.createColorData();
    else
        image.createGreyData();
    for (int i = 0; i < image.size; i++)
    {
        if (image.isColor)
        {
            image.colorData[i] = this->colorData[i] / scalar;
        }
        else
        {
            int temp = round(this->greyData[i] / scalar);
            temp = temp < 0 ? 0 : temp;
            temp = temp > 255 ? 255 : temp;
            image.greyData[i] = temp;
        }
    }
    return image;
}

unsigned char *Image::getRedData()
{
    unsigned char *data = new unsigned char[this->size];
    for (int i = 0; i < this->size; i++)
    {
        data[i] = this->colorData[i].R;
    }
    return data;
}
unsigned char *Image::getGreenData()
{
    unsigned char *data = new unsigned char[this->size];
    for (int i = 0; i < this->size; i++)
    {
        data[i] = this->colorData[i].G;
    }
    return data;
}
unsigned char *Image::getBlueData()
{
    unsigned char *data = new unsigned char[this->size];
    for (int i = 0; i < this->size; i++)
    {
        data[i] = this->colorData[i].B;
    }
    return data;
}
void Image::transformasiLog(float scalar)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->isColor)
        {
            double r = scalar * log(1 + this->colorData[i].R);
            double g = scalar * log(1 + this->colorData[i].G);
            double b = scalar * log(1 + this->colorData[i].B);
            this->colorData[i].R = r > 255 ? 255 : r;
            this->colorData[i].G = g > 255 ? 255 : g;
            this->colorData[i].B = b > 255 ? 255 : b;
        }
        else
        {
            double g = scalar * log(1 + this->greyData[i]);
            this->greyData[i] = g > 255 ? 255 : g;
        }
    }
}
void Image::transformasiLogInv(float scalar)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->isColor)
        {
            double r = pow(exp(this->colorData[i].R), 1/scalar) - 1;
            double g = pow(exp(this->colorData[i].G), 1/scalar) - 1;
            double b = pow(exp(this->colorData[i].B), 1/scalar) - 1;
            r = r < 0 ? 0 : r;
            g = g < 0 ? 0 : g;
            b = b < 0 ? 0 : b;
            this->colorData[i].R = r > 255 ? 255 : r;
            this->colorData[i].G = g > 255 ? 255 : g;
            this->colorData[i].B = b > 255 ? 255 : b;
        }
        else
        {
            double s = pow(exp(this->greyData[i]), 1/scalar) - 1;
            s = s < 0 ? 0 : s;
            this->greyData[i] = s > 255 ? 255 : s;
        }
    }
}

void Image::transformasiPangkat(float scalar, float gamma)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->isColor)
        {
            int r = scalar * pow(this->colorData[i].R, 1 / gamma);
            int g = scalar * pow(this->colorData[i].G, 1 / gamma);
            int b = scalar * pow(this->colorData[i].B, 1 / gamma);
            this->colorData[i].R = r > 255 ? 255 : r;
            this->colorData[i].G = g > 255 ? 255 : g;
            this->colorData[i].B = b > 255 ? 255 : b;
        }
        else
        {
            int g = scalar * pow(this->greyData[i], 1 / gamma);
            this->greyData[i] = g > 255 ? 255 : g;
        }
    }
}

Image *Image::bitPlaneSlicing()
{
    if (this->isColor)
    {
        this->colorToGrayscale();
    }
    Image *plane = new Image[8];
    for (int i = 0; i < 8; i++)
    {
        plane[i] = *this & (1 << i);
        plane[i].tresholding(1);
    }
    return plane;
}

void Image::contrastStretching(int a, int b, float alpha, float beta, float gamma, int ya, int yb)
{
    if (this->isColor)
    {
        for (int i = 0; i < this->size; i++)
        {
            int R = this->colorData[i].R;
            int G = this->colorData[i].G;
            int B = this->colorData[i].B;
            // red
            if (R < a)
                this->colorData[i].R = (alpha * R) > 255 ? 255 : alpha * R;
            else if (R >= b)
                this->colorData[i].R = (gamma * (R - b) + yb) > 255 ? 255 : (gamma * (R - b) + yb);
            else
                this->colorData[i].R = (beta * (R - a) + ya) > 255 ? 255 : (beta * (R - a) + ya);
            // green
            if (G < a)
                this->colorData[i].G = (alpha * G) > 255 ? 255 : (alpha * G);
            else if (G >= b)
                this->colorData[i].G = (gamma * (G - b) + yb) > 255 ? 255 : (gamma * (G - b) + yb);
            else
                this->colorData[i].G = (beta * (G - a) + ya) > 255 ? 255 : (beta * (G - a) + ya);
            // blue
            if (B < a)
                this->colorData[i].B = (alpha * B) > 255 ? 255 : (alpha * B);
            else if (B >= b)
                this->colorData[i].B = (gamma * (B - b) + yb) > 255 ? 255 : (gamma * (B - b) + yb);
            else
                this->colorData[i].B = (beta * (B - a) + ya) > 255 ? 255 : (beta * (B - a) + ya);
        }
    }
    else
    {
        for (int i = 0; i < this->size; i++)
        {
            int val = this->greyData[i];
            if (val < a)
                this->greyData[i] = (alpha * val) > 255 ? 255 : (alpha * val);
            else if (val >= b)
                this->greyData[i] = (gamma * (val - b) + yb) > 255 ? 255 : (gamma * (val - b) + yb);
            else
                this->greyData[i] = (beta * (val - a) + ya) > 255 ? 255 : (beta * (val - a) + ya);
        }
    }
}
void Image ::citraNegativeGrayscale()
{
    if (greyData != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            greyData[i] = 255 - greyData[i];
        }
    }
}

void Image ::citraNegativeColor()
{
    if (colorData != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            colorData[i].R = 255 - colorData[i].R;
            colorData[i].G = 255 - colorData[i].G;
            colorData[i].B = 255 - colorData[i].B;
        }
    }
}

void Image ::brightnessGrayscale(int b)
{
    if (greyData != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            if (greyData[i] + b > 255)
            {
                greyData[i] = 255;
            }
            else if (greyData[i] + b < 0)
            {
                greyData[i] = 0;
            }
            else
            {
                greyData[i] = greyData[i] + b;
            }
        }
    }
}

void Image ::brightnessColorscale(int b)
{
    if (colorData != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            if (colorData[i].R + b > 255)
            {
                colorData[i].R = 255;
            }
            else if (colorData[i].R + b < 0)
            {
                colorData[i].R = 0;
            }
            else
            {
                colorData[i].R = colorData[i].R + b;
            }

            if (colorData[i].G + b > 255)
            {
                colorData[i].G = 255;
            }
            else if (colorData[i].G + b < 0)
            {
                colorData[i].G = 0;
            }
            else
            {
                colorData[i].G = colorData[i].G + b;
            }

            if (colorData[i].B + b > 255)
            {
                colorData[i].B = 255;
            }
            else if (colorData[i].B + b < 0)
            {
                colorData[i].B = 0;
            }
            else
            {
                colorData[i].B = colorData[i].B + b;
            }
        }
    }
}

void Image ::colorToGrayscale()
{
    if (this->isColor)
    {
        this->isColor = false;
        createGreyData();
        for (int i = 0; i < size; i++)
        {
            int gray = (0.3 * (int)colorData[i].R + 0.59 * (int)colorData[i].G + 0.11 * (int)colorData[i].B);
            greyData[i] = gray;
        }
    }
}

void Image::grayLevelSlicing()
{
    if (this->isColor)
    {
        this->colorToGrayscale();
    }
    for (int i = 0; i < this->size; i++)
    {
        if (this->greyData[i] > 142 && this->greyData[i] < 250)
        {
            this->greyData[i] = 255;
        }
        else
        {
            this->greyData[i] = 0;
        }
    }
}

Image Image ::operator&(Image image)
{
    Image newImage;
    if ((this->isColor == true) && (image.isColor == true))
    {
        if (this->width == image.width && this->height == image.height)
        {
            newImage.setWidth(this->width);
            newImage.setHeight(this->height);
            newImage.updateSize();
            newImage.isColor = this->isColor;
            newImage.createColorData();
            for (int i = 0; i < this->size; i++)
            {
                unsigned char r = this->getColorDataByIndex(i).R & image.getColorDataByIndex(i).R;
                unsigned char g = this->getColorDataByIndex(i).G & image.getColorDataByIndex(i).G;
                unsigned char b = this->getColorDataByIndex(i).B & image.getColorDataByIndex(i).B;
                newImage.setColorDataByIndex(i, r, g, b);
            }
        }
    }
    else if ((this->isColor == false) && (image.isColor == false))
    {
        if (this->width == image.width && this->height == image.height)
        {
            newImage.setWidth(this->width);
            newImage.setHeight(this->height);
            newImage.isColor = this->isColor;
            newImage.updateSize();
            newImage.createGreyData();
            for (int i = 0; i < this->size; i++)
            {
                unsigned char c = this->getGreyDataByIndex(i) & image.getGreyDataByIndex(i);
                newImage.setGreyDataByIndex(i, c);
            }
        }
    }
    return newImage;
}

Image Image ::operator&(unsigned char scalar)
{
    Image newImage;
    newImage.setWidth(this->width);
    newImage.setHeight(this->height);
    newImage.updateSize();
    newImage.isColor = this->isColor;
    if (this->isColor)
    {
        newImage.createColorData();
        for (int i = 0; i < this->size; i++)
        {
            unsigned char r = this->getColorDataByIndex(i).R & scalar;
            unsigned char g = this->getColorDataByIndex(i).G & scalar;
            unsigned char b = this->getColorDataByIndex(i).B & scalar;
            newImage.setColorDataByIndex(i, r, g, b);
        }
    }
    else
    {
        newImage.createGreyData();
        for (int i = 0; i < this->size; i++)
        {
            unsigned char c = this->getGreyDataByIndex(i) & scalar;
            newImage.setGreyDataByIndex(i, c);
        }
    }
    return newImage;
}

void Image::tresholding(int t)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->isColor)
        {
            this->colorData[i].R = this->colorData[i].R >= t ? 255 : 0;
            this->colorData[i].G = this->colorData[i].G >= t ? 255 : 0;
            this->colorData[i].B = this->colorData[i].B >= t ? 255 : 0;
        }
        else
        {
            this->greyData[i] = this->greyData[i] >= t ? 255 : 0;
        }
    }
}

void Image::tresholding(int T1, int T2)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->isColor)
        {
            this->colorData[i].R = this->colorData[i].R >= T1 && this->colorData[i].R <= T2 ? 255 : 0;
            this->colorData[i].G = this->colorData[i].G >= T1 && this->colorData[i].G <= T2 ? 255 : 0;
            this->colorData[i].B = this->colorData[i].B >= T1 && this->colorData[i].B <= T2 ? 255 : 0;
        }
        else
        {
            this->greyData[i] = this->greyData[i] >= T1 && this->greyData[i] <= T2 ? 255 : 0;
        }
    }
}

void Image::autoTresholding(int TInit, int delta)
{
    // auto treshold
    int currentT = 9999;
    int newT=TInit;
    long sum1,sum2;
    int count1,count2;
    while(abs(currentT - newT) > delta){
        currentT = newT;
        sum1=0;sum2=0;count1=0;count2=0;
        for (int i=0; i<this->size; i++){
            if (this->greyData[i] >= currentT){
                sum2 += this->greyData[i];
                count2++;
            }else {
                sum1 += this->greyData[i];
                count1++;
            }
        }
        count1 = count1>0 ? count1 : 1;
        count2 = count2>0 ? count2 : 1;
        newT = round((sum1/count1 + sum2/count2) / 2);
    }
    cout << "treshold: " << newT << endl;
    this->tresholding(newT);
}

void Image::thinning(){
    int count;
    int trans;
    int temp[9];
    for(int i=1; i<this->height-1; i++){
        for (int j=1; j<this->width-1; j++){
            if (this->getGreyData(j,i) == 255){
                count=0;
                // check count
                for(int k=-1; k<=1; k++){
                    for (int l=-1; l<=1; l++){
                        count = this->getGreyData(j+l,i+k)==255 ? count+1 : count;
                    }
                }
                if (count>2 && count<8){
                    temp[0] = this->getGreyData(j-1,i-1);
                    temp[1] = this->getGreyData(j,i-1);
                    temp[2] = this->getGreyData(j+1,i-1);
                    temp[3] = this->getGreyData(j+1,i);
                    temp[4] = this->getGreyData(j+1,i+1);
                    temp[5] = this->getGreyData(j,i+1);
                    temp[6] = this->getGreyData(j-1,i+1);
                    temp[7] = this->getGreyData(j-1,i);
                    temp[8] = this->getGreyData(j-1,i-1);
                    trans = 0;
                    for (int m=0; m<8; m++){
                        if (temp[m]==0 && temp[m+1]==1) trans++; 
                    }
                    if (trans==1) this->setGreyData(j,i,0);
                }
            }
        }
    }
}

Image Image ::operator|(Image image)
{
    Image newImage;
    if ((this->isColor == true) && (image.isColor == true))
    {
        if (this->width == image.width && this->height == image.height)
        {
            newImage.setWidth(this->width);
            newImage.setHeight(this->height);
            newImage.updateSize();
            newImage.isColor = this->isColor;
            newImage.createColorData();
            for (int i = 0; i < this->size; i++)
            {
                unsigned char r = this->getColorDataByIndex(i).R | image.getColorDataByIndex(i).R;
                unsigned char g = this->getColorDataByIndex(i).G | image.getColorDataByIndex(i).G;
                unsigned char b = this->getColorDataByIndex(i).B | image.getColorDataByIndex(i).B;
                newImage.setColorDataByIndex(i, r, g, b);
            }
        }
    }
    else if ((this->isColor == false) && (image.isColor == false))
    {
        if (this->width == image.width && this->height == image.height)
        {
            newImage.setWidth(this->width);
            newImage.setHeight(this->height);
            newImage.updateSize();
            newImage.isColor = this->isColor;
            newImage.createGreyData();
            for (int i = 0; i < this->size; i++)
            {
                unsigned char c = this->getGreyDataByIndex(i) | image.getGreyDataByIndex(i);
                newImage.setGreyDataByIndex(i, c);
            }
        }
    }
    return newImage;
}

Image &Image ::operator~()
{
    if (this->isColor == true)
    {
        for (int i = 0; i < this->size; i++)
        {
            unsigned char r = ~this->getColorDataByIndex(i).R;
            unsigned char g = ~this->getColorDataByIndex(i).G;
            unsigned char b = ~this->getColorDataByIndex(i).B;
            this->setColorDataByIndex(i, r, g, b);
        }
    }
    else
    {
        for (int i = 0; i < this->size; i++)
        {
            unsigned char c = ~this->getGreyDataByIndex(i);
            this->setGreyDataByIndex(i, c);
        }
    }
    return *this;
}

Image Image ::rotasi90CW()
{
    Image temp;
    if (this->isColor == true)
    {
        temp.setWidth(this->height);
        temp.setHeight(this->width);
        temp.updateSize();
        temp.createColorData();
        int index = 0;
        for (int i = this->height - 1; i >= 0; i--)
        {
            for (int j = 0; j < this->width; j++)
            {
                unsigned char r = this->getColorDataByIndex(index).R;
                unsigned char g = this->getColorDataByIndex(index).G;
                unsigned char b = this->getColorDataByIndex(index).B;
                temp.setColorData(j, i, r, g, b);
                index++;
            }
        }
    }
    else
    {
        temp.setWidth(this->height);
        temp.setHeight(this->width);
        temp.updateSize();
        temp.createGreyData();
        int index = 0;
        for (int i = this->height - 1; i >= 0; i--)
        {
            for (int j = 0; j < this->width; j++)
            {
                unsigned char c = this->getGreyDataByIndex(index);
                temp.setGreyData(j, i, c);
                index++;
            }
        }
    }
    return temp;
}

Image Image ::rotasi90CCW()
{
    Image temp;
    if (this->isColor == true)
    {
        temp.setWidth(this->height);
        temp.setHeight(this->width);
        temp.updateSize();
        temp.createColorData();
        int index = 0;
        for (int i = 0; i < this->height; i++)
        {
            for (int j = this->width - 1; j >= 0; j--)
            {
                unsigned char r = this->getColorDataByIndex(index).R;
                unsigned char g = this->getColorDataByIndex(index).G;
                unsigned char b = this->getColorDataByIndex(index).B;
                temp.setColorData(j, i, r, g, b);
                index++;
            }
        }
    }
    else
    {
        temp.setWidth(this->height);
        temp.setHeight(this->width);
        temp.updateSize();
        temp.createGreyData();
        int index = 0;
        for (int i = 0; i < this->height; i++)
        {
            for (int j = this->width - 1; j >= 0; j--)
            {
                unsigned char c = this->getGreyDataByIndex(index);
                temp.setGreyData(j, i, c);
                index++;
            }
        }
    }
    return temp;
}

Image Image ::rotasi180()
{
    Image temp;
    if (this->isColor == true)
    {
        temp.setWidth(this->width);
        temp.setHeight(this->height);
        temp.updateSize();
        temp.createColorData();
        int index = 0;
        for (int i = this->height - 1; i >= 0; i--)
        {
            for (int j = this->width - 1; j >= 0; j--)
            {
                unsigned char r = this->getColorDataByIndex(index).R;
                unsigned char g = this->getColorDataByIndex(index).G;
                unsigned char b = this->getColorDataByIndex(index).B;
                temp.setColorData(j, i, r, g, b);
                index++;
            }
        }
    }
    else
    {
        temp.setWidth(this->width);
        temp.setHeight(this->height);
        temp.updateSize();
        temp.createGreyData();
        int index = 0;
        for (int i = this->height - 1; i >= 0; i--)
        {
            for (int j = this->width - 1; j >= 0; j--)
            {
                unsigned char c = this->getGreyDataByIndex(index);
                temp.setGreyData(j, i, c);
                index++;
            }
        }
    }
    return temp;
}

Image Image ::flipping(int type)
{
    Image temp;
    //horizontal
    if (type == 1)
    {
        if (this->isColor == true)
        {
            temp.setWidth(this->width);
            temp.setHeight(this->height);
            temp.updateSize();
            temp.createColorData();
            int index = 0;
            for (int i = this->height - 1; i >= 0; i--)
            {
                for (int j = 0; j < this->width; j++)
                {
                    unsigned char r = this->getColorDataByIndex(index).R;
                    unsigned char g = this->getColorDataByIndex(index).G;
                    unsigned char b = this->getColorDataByIndex(index).B;
                    temp.setColorData(i, j, r, g, b);
                    index++;
                }
            }
        }
        else
        {
            temp.setWidth(this->width);
            temp.setHeight(this->height);
            temp.updateSize();
            temp.createGreyData();
            int index = 0;
            for (int i = this->height - 1; i >= 0; i--)
            {
                for (int j = 0; j < this->width; j++)
                {
                    unsigned char c = this->getGreyDataByIndex(index);
                    temp.setGreyData(i, j, c);
                    index++;
                }
            }
        }
    }
    //vertical
    else if (type == 0)
    {
        if (this->isColor == true)
        {
            temp.setWidth(this->width);
            temp.setHeight(this->height);
            temp.updateSize();
            temp.createColorData();
            int index = 0;
            for (int i = 0; i < this->height; i++)
            {
                for (int j = this->width - 1; j >= 0; j--)
                {
                    unsigned char r = this->getColorDataByIndex(index).R;
                    unsigned char g = this->getColorDataByIndex(index).G;
                    unsigned char b = this->getColorDataByIndex(index).B;
                    temp.setColorData(i, j, r, g, b);
                    index++;
                }
            }
        }
        else
        {
            temp.setWidth(this->width);
            temp.setHeight(this->height);
            temp.updateSize();
            temp.createGreyData();
            int index = 0;
            for (int i = 0; i < this->height; i++)
            {
                for (int j = this->width - 1; j >= 0; j--)
                {
                    unsigned char c = this->getGreyDataByIndex(index);
                    temp.setGreyData(i, j, c);
                    index++;
                }
            }
        }
    }
    return temp;
}

// translasi
Image Image::translasi(int x, int y)
{
    Image *temp = new Image();

    if (this->isColor)
    {
        temp->isColor = true;
        temp->setWidth(this->width);
        temp->setHeight(this->height);
        temp->updateSize();
        temp->createColorData();
        for (int i = 0; i < (this->width); i++)
        {
            for (int j = 0; j < (this->height); j++)
            {
                if (!(i + x < 0) && !(i + x > this->width))
                {
                    if (!(j + y < 0) && !(j + y > this->height))
                    {
                        unsigned char r = getColorData(i, j).R;
                        unsigned char g = getColorData(i, j).G;
                        unsigned char b = getColorData(i, j).B;
                        temp->setColorData(i + x, j + y, r, g, b);
                    }
                }
            }
        }
    }
    else
    {
        temp->isColor = false;
        temp->setWidth(this->width);
        temp->setHeight(this->height);
        temp->updateSize();
        temp->createGreyData();
        for (int i = 0; i < (this->width); i++)
        {
            for (int j = 0; j < (this->height); j++)
            {
                if (!(i + x < 0) && !(i + x > this->width))
                {
                    if (!(j + y < 0) && !(j + y > this->height))
                    {
                        temp->setGreyData(i + x, j + y, this->getGreyData(i, j));
                    }
                }
            }
        }
    }
    return *temp;
}

// zoom in
Image Image::zoomIn()
{
    Image *temp = new Image();
    if (this->isColor)
    { // citra berwarna
        temp->isColor = true;
        temp->setWidth(this->width * 2);
        temp->setHeight(this->height * 2);
        temp->updateSize();
        temp->createColorData();
        int m = 0;
        int n = 0;
        for (int i = 0; i < this->width; i++)
        {
            for (int j = 0; j < this->height; j++)
            {
                unsigned char r = getColorData(i, j).R;
                unsigned char g = getColorData(i, j).G;
                unsigned char b = getColorData(i, j).B;
                temp->setColorData(m, n, r, g, b);
                temp->setColorData(m, n + 1, r, g, b);
                temp->setColorData(m + 1, n, r, g, b);
                temp->setColorData(m + 1, n + 1, r, g, b);
                n = n + 2;
            }
            m = m + 2;
            n = 0;
        }
    }
    else
    { // citra abu
        temp->isColor = false;
        temp->setWidth(this->width * 2);
        temp->setHeight(this->height * 2);
        temp->updateSize();
        temp->createGreyData();
        int m = 0;
        int n = 0;
        for (int i = 0; i < this->width; i++)
        {
            for (int j = 0; j < this->height; j++)
            {
                temp->setGreyData(m, n, this->getGreyData(i, j));
                temp->setGreyData(m, n + 1, this->getGreyData(i, j));
                temp->setGreyData(m + 1, n, this->getGreyData(i, j));
                temp->setGreyData(m + 1, n + 1, this->getGreyData(i, j));
                n = n + 2;
            }
            m = m + 2;
            n = 0;
        }
    }
    return *temp;
}

// zoom out
Image Image::zoomOut()
{
    Image *temp = new Image();
    if (this->isColor)
    {
        temp->isColor = true;
        temp->setWidth(this->width / 2);
        temp->setHeight(this->height / 2);
        temp->updateSize();
        temp->createColorData();
        int m = 0;
        int n = 0;
        for (int i = 0; i < temp->width; i++)
        {
            for (int j = 0; j < temp->height; j++)
            {
                unsigned char p1_1_r = this->getColorData(m, n).R;
                unsigned char p1_2_r = this->getColorData(m, n + 1).R;
                unsigned char p2_1_r = this->getColorData(m + 1, n).R;
                unsigned char p2_2_r = this->getColorData(m + 1, n + 1).R;
                unsigned char p1_1_g = this->getColorData(m, n).G;
                unsigned char p1_2_g = this->getColorData(m, n + 1).G;
                unsigned char p2_1_g = this->getColorData(m + 1, n).G;
                unsigned char p2_2_g = this->getColorData(m + 1, n + 1).G;
                unsigned char p1_1_b = this->getColorData(m, n).B;
                unsigned char p1_2_b = this->getColorData(m, n + 1).B;
                unsigned char p2_1_b = this->getColorData(m + 1, n).B;
                unsigned char p2_2_b = this->getColorData(m + 1, n + 1).B;
                int meanPixelR = (p1_1_r + p1_2_r + p2_1_r + p2_2_r) / 4;
                int meanPixelG = (p1_1_g + p1_2_g + p2_1_g + p2_2_g) / 4;
                int meanPixelB = (p1_1_b + p1_2_b + p2_1_b + p2_2_b) / 4;
                temp->setColorData(i, j, meanPixelR, meanPixelG, meanPixelB);
                n = n + 2;
            }
            m = m + 2;
            n = 0;
        }
    }
    else
    {
        temp->isColor = false;
        temp->setWidth(this->width / 2);
        temp->setHeight(this->height / 2);
        temp->updateSize();
        temp->createGreyData();
        int m = 0;
        int n = 0;
        for (int i = 0; i < temp->width; i++)
        {
            for (int j = 0; j < temp->height; j++)
            {
                unsigned char p1_1 = this->getGreyData(m, n);
                unsigned char p1_2 = this->getGreyData(m, n + 1);
                unsigned char p2_1 = this->getGreyData(m + 1, n);
                unsigned char p2_2 = this->getGreyData(m + 1, n + 1);
                int meanPixel = (p1_1 + p1_2 + p2_1 + p2_2) / 4;
                temp->setGreyData(i, j, meanPixel);
                n = n + 2;
            }
            m = m + 2;
            n = 0;
        }
    }
    return *temp;
}

void Image::konvolusi(float *filter, int n)
{
    int tempHeight = this->height - n + 1;
    int tempWidth = this->width - n + 1;
    unsigned int *temp;
    Color *tempC;
    if (this->isColor)
    {
        tempC = new Color[tempHeight * tempWidth];
    }
    else
    {
        temp = new unsigned int[tempHeight * tempWidth];
    }
    for (int i = 0; i < tempHeight; i++)
    {
        for (int j = 0; j < tempWidth; j++)
        {
            // operasi dot
            int sum = 0;
            int sumR = 0, sumG = 0, sumB = 0;
            for (int k = 0; k < n; k++)
            {
                for (int l = 0; l < n; l++)
                {
                    if (this->isColor)
                    {
                        sumR += filter[k * n + l] * this->getColorData(j + l, i + k).R;
                        sumG += filter[k * n + l] * this->getColorData(j + l, i + k).G;
                        sumB += filter[k * n + l] * this->getColorData(j + l, i + k).B;
                    }
                    else
                    {
                        sum += filter[k * n + l] * this->getGreyData(j + l, i + k);
                    }
                }
            }
            // clipping
            if (this->isColor)
            {
                sumR = sumR < 0 ? 0 : sumR;
                tempC[i * tempHeight + j].R = sumR > 255 ? 255 : sumR;
                sumG = sumG < 0 ? 0 : sumG;
                tempC[i * tempHeight + j].G = sumG > 255 ? 255 : sumG;
                sumB = sumB < 0 ? 0 : sumB;
                tempC[i * tempHeight + j].B = sumB > 255 ? 255 : sumB;
            }
            else
            {
                sum = sum < 0 ? 0 : sum;
                temp[i * tempHeight + j] = sum > 255 ? 255 : sum;
            }
        }
    }
    int offset = (n - 1) / 2;
    for (int i = 0; i < tempHeight; i++)
    {
        for (int j = 0; j < tempWidth; j++)
        {
            if (this->isColor)
            {
                this->setColorData(j + offset, i + offset, tempC[i * tempHeight + j].R, tempC[i * tempHeight + j].G, tempC[i * tempHeight + j].B);
            }
            else
            {
                this->setGreyData(j + offset, i + offset, temp[i * tempHeight + j]);
            }
        }
    }
    if (this->isColor)
    {
        delete[] tempC;
    }
    else
    {
        delete[] temp;
    }
}

void Image::konvolusi(float *filterX, float *filterY, int n)
{
    int tempHeight = this->height - n + 1;
    int tempWidth = this->width - n + 1;
    unsigned int *temp;
    Color *tempC;
    if (this->isColor)
    {
        tempC = new Color[tempHeight * tempWidth];
    }
    else
    {
        temp = new unsigned int[tempHeight * tempWidth];
    }
    for (int i = 0; i < tempHeight; i++)
    {
        for (int j = 0; j < tempWidth; j++)
        {
            // operasi dot
            int sumX = 0, sumY = 0;
            int sumXR = 0, sumXG = 0, sumXB = 0;
            int sumYR = 0, sumYG = 0, sumYB = 0;
            for (int k = 0; k < n; k++)
            {
                for (int l = 0; l < n; l++)
                {
                    if (this->isColor)
                    {
                        sumXR += filterX[k * n + l] * this->getColorData(j + l, i + k).R;
                        sumXG += filterX[k * n + l] * this->getColorData(j + l, i + k).G;
                        sumXB += filterX[k * n + l] * this->getColorData(j + l, i + k).B;
                        sumYR += filterY[k * n + l] * this->getColorData(j + l, i + k).R;
                        sumYG += filterY[k * n + l] * this->getColorData(j + l, i + k).G;
                        sumYB += filterY[k * n + l] * this->getColorData(j + l, i + k).B;
                    }
                    else
                    {
                        sumX += filterX[k * n + l] * this->getGreyData(j + l, i + k);
                        sumY += filterY[k * n + l] * this->getGreyData(j + l, i + k);
                    }
                }
            }
            // clipping
            if (this->isColor)
            {
                int sumR = abs(sumXR) + abs(sumYR);
                tempC[i * tempHeight + j].R = sumR > 255 ? 255 : sumR;
                int sumG = abs(sumXG) + abs(sumYG);
                tempC[i * tempHeight + j].G = sumG > 255 ? 255 : sumG;
                int sumB = abs(sumXB) + abs(sumYB);
                tempC[i * tempHeight + j].B = sumB > 255 ? 255 : sumB;
            }
            else
            {
                int sum = abs(sumX) + abs(sumY);
                temp[i * tempHeight + j] = sum > 255 ? 255 : sum;
            }
        }
    }
    int offset = (n - 1) / 2;
    for (int i = 0; i < tempHeight; i++)
    {
        for (int j = 0; j < tempWidth; j++)
        {
            if (this->isColor)
            {
                this->setColorData(j + offset, i + offset, tempC[i * tempHeight + j].R, tempC[i * tempHeight + j].G, tempC[i * tempHeight + j].B);
            }
            else
            {
                this->setGreyData(j + offset, i + offset, temp[i * tempHeight + j]);
            }
        }
    }
    if (this->isColor)
    {
        delete[] tempC;
    }
    else
    {
        delete[] temp;
    }
}

void Image::highPassFilter(int fil)
{
    std::vector<float> filter;
    switch (fil)
    {
    case 0:
        filter = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
        break;
    case 1:
        filter = {-1, -1, -1, -1, 9, -1, -1, -1, -1};
    case 2:
        filter = {0, -1, 0, -1, 5, -1, 0, -1, 0};
    case 3:
        filter = {1, -2, 1, -2, 5, -2, 1, -2, 1};
    case 4:
        filter = {1, -2, 1, -2, 4, -2, 1, -2, 1};
    case 5:
        filter = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    default:
        filter = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
        break;
    }
    this->konvolusi(&filter[0]);
}

void Image::meanFilter()
{
    float filter[9] = {1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f};
    this->konvolusi(filter);
}

void Image::gaussianSmoothing()
{
    float filter[9] = {1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f, 2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f};
    this->konvolusi(filter);
}

void Image::unsharpMasking()
{
    // lowpass menggunakan meanfilter
    float filter[9] = {-1.0f / 9.0f, -1.0f / 9.0f, -1.0f / 9.0f, -1.0f / 9.0f, 17.0f / 9.0f, -1.0f / 9.0f, -1.0f / 9.0f, -1.0f / 9.0f, -1.0f / 9.0f};
    this->konvolusi(filter);
}

void Image::highBoost(float c)
{
    // lowpass menggunakan meanfilter
    float filter[9] = {-1.0f / 9.0f * c, -1.0f / 9.0f * c, -1.0f / 9.0f * c, -1.0f / 9.0f * c, 17.0f / 9.0f * c, -1.0f / 9.0f * c, -1.0f / 9.0f * c, -1.0f / 9.0f * c, -1.0f / 9.0f * c};
    this->konvolusi(filter);
}

void Image::gaussian()
{
    float filterX[4] = {-1, 1, -1, 1};
    float filterY[4] = {1, 1, -1, -1};
    this->konvolusi(filterX, filterY, 2);
}

void Image::laplace()
{
    float filter[9] = {0, 1, 0, 1, -4, 1, 0, 1, 0};
    this->konvolusi(filter);
}

void Image::loG()
{
    float filter[25] = {0, 0, -1, 0, 0,
                        0, -1, -2, -1, 0,
                        -1, -2, 16, -2, -1,
                        0, -1, -2, -1, 0,
                        0, 0, -1, 0, 0};
    this->konvolusi(filter, 5);
}

void Image::sobel()
{
    float filterX[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    float filterY[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    this->konvolusi(filterX, filterY);
}

void Image::prewitt()
{
    float filterX[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    float filterY[9] = {1, 1, 1, 0, 0, 0, -1, -1, -1};
    this->konvolusi(filterX, filterY);
}

void Image::roberts()
{
    float filter1[4] = {1, 0, 0, -1};
    float filter2[4] = {0, 1, -1, 0};
    this->konvolusi(filter1, filter2);
}

void Image::canny(int t)
{
    this->gaussianSmoothing();
    this->sobel();
    this->tresholding(t);
}

void Image::transformFourier(){
    double tetha;
    double* real = new double[this->size];
    double* imaginer = new double[this->size];
    for (int i=0; i<this->size; i++) { 
        real[i]=0;
        imaginer[i]=0;
    }
    for (int i=0; i<this->size; i++){
         for (int j=0; j<this->size-1; j++){
            tetha= i*2*3.14*j/(double)this->size;
            real[i]=real[i]+(this->greyData[j]*cos(tetha))/(double)this->size;
            imaginer[i]=imaginer[i]-(this->greyData[j]*sin(tetha))/(double)this->size;
         }
    }
    for (int i=0; i<this->size; i++){
        double spektrum = sqrt(pow(real[i],2) + pow(imaginer[i],2));
        this->greyData[i] = (unsigned char) spektrum;
    }
}

void Image::show() {
    cout << "height: " << this->height << endl;
    cout << "width: " << this->width << endl;
    cout << "size: " << this->size << endl;
    cout << "isColor: " << this->isColor << endl;
    cout << "data: " << endl;
    if (this->isColor){
        for (int i=0; i<10; i++){
            cout << "(" << (int)this->colorData[i].R << "," << (int)this->colorData[i].G << "," << (int)this->colorData[i].B << ")" <<endl;
        }
    }else {
        for (int i=0; i<10; i++){
            cout << (unsigned int)this->greyData[i] << endl;
        }
    }
}