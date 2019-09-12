#ifndef RAW_HPP
#define RAW_HPP
#include "Image.hpp"
#include <string>

using std::string;
class RAW
{
public:
    string filename;
    RAW(string filename);
    
    void readFile(Image& image, bool isColor);
    void writeFile(Image image, string filename);
};

#endif