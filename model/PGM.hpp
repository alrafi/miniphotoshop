#include "Image.hpp"
#include <string>

using std::string;
class PGM
{
public:
    string filename;

    PGM(string filename);

    Image readFile();
    void writeFile(Image image);
};