#ifndef BMP_HPP
#define BMP_HPP
#include "Image.hpp"
#include <string>

struct Header {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1, reserved2;
    unsigned int offset;    
};

struct InfoHeader {
    unsigned int size;
    int width,height;
    unsigned short int planes;
    unsigned short int bits;
    unsigned int compression;
    unsigned int imageSize;
    int xResolution,yResolution;
    unsigned int nColours;
    unsigned int importantColours;
};

using std::string;
class BMP
{
public:
    string filename;
    Header header;
    InfoHeader infoHeader;

    BMP(string filename);

    void readFile(Image& image);
    void writeFile(Image image, string filename);
};
#endif