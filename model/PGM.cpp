#include "PGM.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;
PGM :: PGM(string filename){
    this->filename = filename;
}

void PGM :: readFile(Image& thisImage){
    ifstream imagefile;
    imagefile.open(filename);
    string line;
    
    int width;
    int height;
    int scale;
    bool isColor = false;

    int i=0;
    int index=0;
    while(getline(imagefile, line)){
        if(line[0] == '#'){
            continue;
        }
        if(i == 0){
            if (line.compare("P2") != 0){
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
            i++;
            continue;
        }
        if (i == 2){
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> tokens(beg, end);
            scale = stoi(tokens[0]);
            thisImage.createGreyData();
            i++;
            continue;
        }
        if (i > 2){
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> tokens(beg, end);
            for (auto& s : tokens){
                unsigned char a = ((255/scale) * stoi(s));
                thisImage.setGreyDataByIndex(index, a);
                index++;
            }
            i++;
            continue;
        }
    }
    imagefile.close();
}

void PGM :: writeFile(Image thisImage, string filename){
    // cout << "on progress" << endl;
    ofstream file;
    file.open(filename + ".pgm");
    file << "P2" << endl;
    file << "# created by lenanudelovers" << endl;
    file << thisImage.width <<"  "<< thisImage.height << endl;
    file << "255" << endl;
    int line = 0;
    for (int i= 0; i<thisImage.size; i++){
        file << (unsigned int)thisImage.getGreyDataByIndex(i);
        line++;
        if(line > 13){
            file << endl;
            line = 0;
        }else{
            file << "  ";
        }
    }
    file.close();
}