#ifndef Spektrum_HPP
#define Spektrum_HPP
#include "Image.hpp"
class Spektrum
{
    public: 
        int size, width, height;
        double* real;
        double* imag;
        Spektrum(const Image &img);
        ~Spektrum();
        Image& getSpektrum();
        Image& balikan();
        void show();
};
#endif