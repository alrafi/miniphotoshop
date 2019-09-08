#include "PBM.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>


using namespace std;


PBM :: PBM(string filename){
    this->filename = filename;
}

void PBM :: readFile(Image& thisImage){
    ifstream imagefile;
    imagefile.open(filename);
    string line;
    
    int width;
    int height;
    bool isColor = false;

    int i=0;
    int index=0;
    while(getline(imagefile, line)){
        if(line[0] == '#'){
            continue;
        }
        if(i == 0){
            if (line.compare("P1") != 0){
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
            thisImage.createGreyData();
            i++;
            continue;
        }
        if (i > 1){
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> tokens(beg, end);
            for (auto& s : tokens){
                unsigned char a;
                if(s == "1"){
                    a = 0;
                }else{
                    a = 255;
                }
                thisImage.setGreyDataByIndex(index, a);
                index++;
            }
            i++;
            continue;
        }
    }
    imagefile.close();
}

void PBM :: writeFile(Image thisImage, string filename){
    ofstream file;
    file.open(filename + ".pbm");
    file << "P1" << endl;
    file << "# created by lenanudelovers" << endl;
    file << thisImage.width <<"  "<< thisImage.height << endl;
    int line = 0;
    for (int i= 0; i<thisImage.size; i++){
        if ((unsigned int)thisImage.getGreyDataByIndex(i) == 255){
            file << "0";    
        }else{
            file << "1";
        }
        line++;
        if(line > 22){
            file << endl;
            line = 0;
        }else{
            file << "  ";
        }
    }
    file.close();
}