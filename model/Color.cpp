#include "Color.hpp"
Color::Color(){
    R = 0;
    G = 0;
    B = 0:
}

Color::Color(unsigned char R, unsigned char G, unsigned char B){
    this->R = R;
    this->G = G;
    this->B = B;
}

void Color::setColor(unsigned char R, unsigned char G, unsigned char B){
    this->R = R;
    this->G = G;
    this->B = B;
}
