#ifndef IMAGE_HPP
#define IMAGE_HPP
#include "Color.hpp"
class Image
{
public:
    //atribute
    Color *colorData;
    unsigned char *greyData;
    int width;
    int height;
    int size;
    bool isColor;

    //constructor
    Image();
    Image(int width, int height, bool isColor);
    Image(const Image &img);

    //destroyer
    ~Image();

    void addImage(const Image &img);
    //data constructor
    void createColorData();
    void createGreyData();

    //data destructor
    void deleteColorData();
    void deleteGreyData();

    //setter attribute
    void setWidth(int width);
    void setHeight(int height);
    void setColor(bool isColor);

    //call this method when you want to update size of image, this func will set the size with updated width and updated heigth
    void updateSize();

    //method setColorData
    void setColorData(int x, int y, unsigned char R, unsigned char G, unsigned char B);

    //method setGreyData
    void setGreyData(int x, int y, unsigned char grey);

    //method setColorData by Index
    void setColorDataByIndex(int index, unsigned char R, unsigned char G, unsigned char B);

    //method setGreyData by Index
    void setGreyDataByIndex(int index, unsigned char grey);

    //method to getcolordata by index
    Color getColorDataByIndex(int index);

    //method to getgreydata by index
    unsigned char getGreyDataByIndex(int index);

    //method getColorData
    Color getColorData(int x, int y);

    //method getGreyData
    unsigned char getGreyData(int x, int y);

    unsigned char *getRedData();
    unsigned char *getGreenData();
    unsigned char *getBlueData();

    //method operator image
    Image operator+(Image const &img);
    Image operator+(int scalar);
    Image operator-(Image const &img);
    Image operator-(int scalar);
    Image&operator=(const Image &img);
    Image operator*(const Image &img);
    Image operator*(int scalar);
    Image operator*(float scalar);
    Image operator/(int scalar);
    Image operator/(float scalar);

    // transformasi log
    void transformasiLog(float scalar);
    void transformasiLogInv(float scalar);
    void transformasiPangkat(float scalar, float gamma);

    // bit plane slicing
    Image *bitPlaneSlicing();

    // contrast stretching
    void contrastStretching(int a, int b, float alpha, float beta, float gamma, int ya, int yb);
    //menthod grayscale citra negative
    void citraNegativeGrayscale();

    //method color citra negative
    void citraNegativeColor();

    //method brightening grayscale
    void brightnessGrayscale(int b);

    //method brightening color
    void brightnessColorscale(int b);

    //method color to grayscale
    void colorToGrayscale();

    // method tresholding
    // standard
    void tresholding(int T);
    // object in range T1, T2
    void tresholding(int T1, int T2);
    // automatic tresholding
    void autoTresholding(int TInit, int delta);

    void thinning();
    void dilation(int loop=1);
    void CCL(int **hasil, int *sum);
    void penapisRatio(float r1, float r2);
    void penapisArea(int a1, int a2);
    void crop(const Image& mask);
    void crop();
    void resizePixels(int w2, int h2);
    Image* ekstraksi(Image smearing, int *count);
    void smearing(int treshold);
    int pixelMatching(Image& image);
    // method gray level slicing
    void grayLevelSlicing();

    //operasi boolean
    //operasi and
    Image operator&(Image image);
    Image operator&(unsigned char scalar);
    //operasi or
    Image operator|(Image image);
    Image operator|(unsigned char scalar);
    //operasi not
    Image &operator~();

    //operasi geometri
    //rotasi
    Image rotasi90CW();
    Image rotasi90CCW();
    Image rotasi180();
    //flipping
    Image flipping(int type);
    // Translasi
    Image translasi(int x, int y);
    // zoom in
    Image zoomIn();
    // zoom out
    Image zoomOut();
    //convolution
    void konvolusi(float *filter, int n = 3);
    void konvolusi(float *filterX, float *filterY, int n = 3);
    void highPassFilter(int fil = 0);
    void meanFilter();
    void gaussianSmoothing();
    void unsharpMasking();
    void highBoost(float c);
    // edge detection
    void gaussian();
    void laplace();
    void loG();
    void sobel();
    void prewitt();
    void roberts();
    void canny(int t);
    // transformasi fourier
    void transformFourier();
    void show();
};
#endif