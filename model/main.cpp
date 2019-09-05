#include "PGM.hpp"
#include <iostream>

using namespace std;

int main(){
    PGM pgm("baboon.ascii.pgm");
    Image image;
    pgm.readFile(image);

    cout << image.width << endl;
    cout << image.height << endl;
    for(int i = 0; i<10; i++){
        cout << (unsigned int) image.greyData[i] << endl;
    }
    pgm.writeFile(image, "anjay");
    return 0;
}