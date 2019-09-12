#ifndef PBM_HPP
#define PBN_HPP

#include "Image.hpp"
#include <string>

using std::string;

class PBM{
    
    public:
        string filename;
    
        PBM(string filename);

        void readFile(Image& image);
        void writeFile(Image image, string filename);
};

#endif