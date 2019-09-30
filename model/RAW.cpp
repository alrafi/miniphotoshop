#include "RAW.hpp"
#include <iostream>
#include <fstream>
#include <iterator>

using namespace std;

RAW :: RAW(string filename){
    this->filename = filename;
}

void RAW :: readFile(Image& thisImage, bool isColor = false){
    ifstream imagefile;
    imagefile.open(filename);

    thisImage.setColor(isColor);
    unsigned short height, width;
    imagefile.read((char *) &height, sizeof(unsigned short));
    imagefile.read((char *) &width, sizeof(unsigned short));
    thisImage.setHeight(height);
    thisImage.setWidth(width);
    if (isColor) {
        thisImage.createColorData();
    }else {
        thisImage.createGreyData();
    }

    for (int i=0; i<thisImage.height; i++) {
        for (int j=0; j<thisImage.width; j++) {
            if (isColor) {
                unsigned char r,g,b;
                imagefile.read((char*) &r, 1);
                imagefile.read((char*) &g, 1);
                imagefile.read((char*) &b, 1);
                thisImage.setColorData(i,j,r,g,b);
            } else {
                unsigned char c;
                imagefile.read((char*) &c,1);
                thisImage.setGreyData(i,j,c);
            }
        }
    }

    imagefile.close();
}

void RAW :: writeFile(Image thisImage, string filename){
    ofstream file;
    file.open(filename + ".raw");
    unsigned short height = thisImage.height;
    unsigned short width = thisImage.width;
    file.write((char *) &thisImage.height, sizeof(unsigned short));
    file.write((char *) &thisImage.width,sizeof(unsigned short));

    for (int i=0; i<thisImage.height; i++) {
        for (int j=0; j<thisImage.width; j ++) {
            if (thisImage.isColor) {
                Color c = thisImage.getColorData(i,j);
                file.write((char *) &c.R, 1);
                file.write((char *) &c.G, 1);
                file.write((char *) &c.B, 1);
            } else {
                unsigned char c = thisImage.getGreyData(i,j);
                file.write((char *) &c, 1);
            }
        }
    }

    file.close();
}