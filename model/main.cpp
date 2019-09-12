#include "PPM.hpp"
#include "PGM.hpp"
#include <iostream>

using namespace std;

int main(){
    PPM ppm("pbmlib.ascii.ppm");
    PGM pgm("hfjhfjh.pbm");
    Image image;
    ppm.readFile(image);

    cout << image.width << endl;
    cout << image.height << endl;
    for(int i = 0; i<10; i++){
        cout << (unsigned int) image.colorData[i].R << "  " << (unsigned int) image.colorData[i].G << "  " << (unsigned int) image.colorData[i].B << endl;
    }
    image.colorToGrayscale();
    pgm.writeFile(image, "itemputih");
    return 0;
}