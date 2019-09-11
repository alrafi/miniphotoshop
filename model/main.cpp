<<<<<<< HEAD
#include "PBM.hpp"
=======
#include "PPM.hpp"
>>>>>>> 9eb4a414bf502fbab35b76609000de4ee92987a5
#include <iostream>

using namespace std;

int main(){
<<<<<<< HEAD
    PBM pbm("circle.ascii.pbm");
    Image image;
    pbm.readFile(image);
=======
    PPM ppm("blackbuck.ascii.ppm");
    Image image;
    ppm.readFile(image);
>>>>>>> 9eb4a414bf502fbab35b76609000de4ee92987a5

    cout << image.width << endl;
    cout << image.height << endl;
    for(int i = 0; i<10; i++){
<<<<<<< HEAD
        if ((unsigned int) image.greyData[i] == 255){
            cout << "0" << endl;
        }else{
            cout << "1" << endl;
        }    
    }
    pbm.writeFile(image, "anjay2");
=======
        cout << (unsigned int) image.colorData[i].R << "  " << (unsigned int) image.colorData[i].G << "  " << (unsigned int) image.colorData[i].B << endl;
    }
    ppm.writeFile(image, "anjay1");
>>>>>>> 9eb4a414bf502fbab35b76609000de4ee92987a5
    return 0;
}