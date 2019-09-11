#ifndef PPM_HPP
#define PPM_HPP
#include "Image.hpp"
#include <string>

using std::string;
class PPM
{
public:
    string filename;
    PPM(string filename);
    
    void readFile(Image& image);
    void writeFile(Image image, string filename);
};

#endif