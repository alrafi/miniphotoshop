#include "BMP.hpp"
#include <iostream>
#include <fstream>
#include <iterator>

using namespace std;
BMP :: BMP(string filename){
    this->filename = filename;
}

void BMP :: readFile(Image& thisImage){
    ifstream imagefile;
    imagefile.open(filename);
    string line;
    
    int width;
    int height;
    int scale;
    bool isColor = false;

    // read header
    cout << "-------------Header------------" << endl;
    // imagefile.read( (char *) &(this->header), 14);
    imagefile.read((char*) &(this->header.type), 2);
    imagefile.read((char*) &(this->header.size), 4);
    imagefile.read((char*) &(this->header.reserved1), 2);
    imagefile.read((char*) &(this->header.reserved2), 2);
    imagefile.read((char*) &(this->header.offset), 4);
    cout << "type:      " << this->header.type << endl;
    cout << "size:      " << this->header.size << endl;
    cout << "reserved1: " << this->header.reserved1 << endl;
    cout << "reserved2: " << this->header.reserved2 << endl;
    cout << "offset:    " << this->header.offset << endl;

    // read info header
    cout << "-------------InfoHeader------------" << endl;
    imagefile.read( (char *) &(this->infoHeader), 40);
    cout << "size:              " << this->infoHeader.size << endl;
    cout << "width:             " << this->infoHeader.width << endl;
    cout << "height:            " << this->infoHeader.height << endl;
    cout << "planes:            " << this->infoHeader.planes << endl;
    cout << "bits:              " << this->infoHeader.bits << endl;
    cout << "compression:       " << this->infoHeader.compression << endl;
    cout << "image size:        " << this->infoHeader.imageSize << endl;
    cout << "x resolution:      " << this->infoHeader.xResolution << endl;
    cout << "y resolution:      " << this->infoHeader.yResolution << endl;
    cout << "n colours:         " << this->infoHeader.nColours << endl;
    cout << "important colours: " << this->infoHeader.importantColours << endl;

    unsigned char c;
    // check if have color palette
    Color* palette = new Color[this->infoHeader.nColours];
    if (this->infoHeader.nColours) {
        // read color palette
        for (int i=0; i < this->infoHeader.nColours; i++) {
            imagefile >> palette[i].R;
            imagefile >> palette[i].G;
            imagefile >> palette[i].B;
            imagefile >> c;
        }
    }

    // create image
    thisImage.setWidth(this->infoHeader.width);
    thisImage.setHeight(this->infoHeader.height);
    thisImage.setColor(this->infoHeader.nColours || this->infoHeader.bits == 24);
    thisImage.updateSize();
    if (thisImage.isColor) {
        thisImage.createColorData();
    } else {
        thisImage.createGreyData();
    }
    
    // read image data
    imagefile.seekg(this->header.offset, imagefile.beg);
    for (int i = 0; i < this->infoHeader.height; i++) {
        for (int j = 0; j < this->infoHeader.width; j++) {
            if (this->infoHeader.nColours) {
                imagefile.read((char *) &c, 1);
                int index = c;
                thisImage.setColorData(j,i,palette[index].R, palette[index].G, palette[index].B);
            } else if (this->infoHeader.bits == 24) {
                unsigned char r,g,b;
                imagefile.read((char *)&b, 1);
                imagefile.read((char *)&g, 1);
                imagefile.read((char *)&r, 1);
                thisImage.setColorData(j,i,r,g,b);
            } else {
                imagefile.read ((char *) &c, 1);
                thisImage.setGreyData(j,i,c);
            }
        }
    }
    cout << "data" << endl;
    if (thisImage.isColor) {
        for (int i=0; i < 20; i++) {
            cout << (int) thisImage.colorData[i].R << ","
            << (int) thisImage.colorData[i].G << ","
            << (int) thisImage.colorData[i].B << "," << endl;
        }
    } else {
        for (int i=0; i < 20; i++) {
            cout << (int) thisImage.greyData[i] << endl;
        }
    }

    if (palette) {
        delete[] palette;
    }
}

void BMP :: writeFile(Image thisImage, string filename){

    ofstream file;
    file.open(filename + ".bmp");

    // create header
    Header header;
    header.type = 19778;
    header.size = 54 + thisImage.size * (thisImage.isColor ? 3 : 1);
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.offset = 54; // offset
    //write header
    file.write((char *) &header.type, 2);
    file.write((char *) &header.size, 4);
    file.write((char *) &header.reserved1, 2);
    file.write((char *) &header.reserved2, 2);
    file.write((char *) &header.offset, 4);

    // create info header
    InfoHeader infoHeader;
    infoHeader.size = 40;
    infoHeader.width = thisImage.width;
    infoHeader.height = thisImage.height;
    infoHeader.planes = 1;
    infoHeader.bits = thisImage.isColor ? 24 : 8;
    infoHeader.compression = 0;
    infoHeader.imageSize = thisImage.size * (thisImage.isColor ? 3:1);
    infoHeader.xResolution = 2834;
    infoHeader.yResolution = 2834;
    infoHeader.nColours = 0;
    infoHeader.importantColours = 0;
    // write info header
    file.write((char *) &infoHeader, 40);

    // write imageData
    for (int i=0; i < thisImage.size;i++) {
        if (thisImage.isColor) {
            file.write((char *) &thisImage.colorData[i].R, 1);
            file.write((char *) &thisImage.colorData[i].G, 1);
            file.write((char *) &thisImage.colorData[i].B, 1);
        } else {
            file.write((char *) &thisImage.greyData[i], 1);
        }
    }

    file.close();
}