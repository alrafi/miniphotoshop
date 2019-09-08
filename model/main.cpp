#include "PPM.hpp"
#include <iostream>

using namespace std;

int main(){
    PPM ppm("blackbuck.ascii.ppm");
    Image image;
    ppm.readFile(image);

    cout << image.width << endl;
    cout << image.height << endl;
    for(int i = 0; i<10; i++){
        cout << (unsigned int) image.colorData[i].R << "  " << (unsigned int) image.colorData[i].G << "  " << (unsigned int) image.colorData[i].B << endl;
    }
    ppm.writeFile(image, "anjay1");
    return 0;
}