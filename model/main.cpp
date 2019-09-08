#include "PBM.hpp"
#include <iostream>

using namespace std;

int main(){
    PBM pbm("circle.ascii.pbm");
    Image image;
    pbm.readFile(image);

    cout << image.width << endl;
    cout << image.height << endl;
    for(int i = 0; i<10; i++){
        if ((unsigned int) image.greyData[i] == 255){
            cout << "0" << endl;
        }else{
            cout << "1" << endl;
        }    
    }
    pbm.writeFile(image, "anjay2");
    return 0;
}