#ifndef PGM_HPP
#define PGM_HPP
#include "Image.hpp"
#include <string>

using std::string;
class PGM
{
public:
    string filename;

    PGM(string filename);

    void readFile(Image& image);
    void writeFile(Image image, string filename);
};
#endif