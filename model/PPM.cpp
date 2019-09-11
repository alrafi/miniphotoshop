#include "PPM.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

PPM :: PPM(string filename){
    this->filename = filename;
}

void PPM :: readFile(Image& thisImage){
    ifstream imagefile;
    imagefile.open(filename);
    string line;

    int width;
    int height;
    int scale;
    bool isColor = true;
    unsigned char *temporaryColorData;

    int i=0;
    int index = 0;
    while(getline(imagefile, line)){
        if(line[0] == '#'){
            continue;
        }
        if(i == 0){
            if (line.compare("P3") != 0){
                cout << "file is not supported" << endl;
                break;
            }else{
                i++;
                continue;
            }
        }
        if (i == 1){
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> tokens(beg, end);
            width = stoi(tokens[0]);
            height = stoi(tokens[1]);
            thisImage.setWidth(width);
            thisImage.setHeight(height);
            thisImage.updateSize();
            temporaryColorData = new unsigned char[thisImage.size * 3];
            i++;
            continue;
        }
        if (i == 2){
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> tokens(beg, end);
            scale = stoi(tokens[0]);
            thisImage.createColorData();
            i++;
            continue;
        }
        if (i > 2){
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> tokens(beg, end);
            for (auto& s : tokens){
                unsigned char a = ((255/scale) * stoi(s));
                temporaryColorData[index] = a;
                index++;
            }
            i++;
            continue;
        }
    }
    int y=0;
    for(int j=0; j<(thisImage.size*3); j= j+3){
        thisImage.setColorDataByIndex(y, temporaryColorData[j], temporaryColorData[j+1], temporaryColorData[j+2]);
        y++;
    }
    delete[] temporaryColorData;
    imagefile.close();
}

void PPM :: writeFile(Image thisImage, string filename){
    // cout << "on progress" << endl;
    ofstream file;
    file.open(filename + ".ppm");
    file << "P3" << endl;
    file << "# created by lenanudelovers" << endl;
    file << thisImage.width <<"  "<< thisImage.height << endl;
    file << "255" << endl;
    int line = 0;
    for (int i= 0; i<thisImage.size; i++){
        Color color = thisImage.getColorDataByIndex(i);
        file <<(unsigned int) color.R << "  " <<(unsigned int) color.G << "  " <<(unsigned int) color.B;
        line++;
        if(line > 3){
            file << endl;
            line = 0;
        }else{
            file << "  ";
        }
    }
    file.close();
}