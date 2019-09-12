#include "Color.hpp"
Color::Color(){
    R = 0;
    G = 0;
    B = 0;
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

bool Color::operator==(Color& color){
    return (this->R == color.R)
        && (this->G == color.G)
        && (this->B == color.B);
}

bool Color::operator<(const Color& color) const{
    return (this->R + this->G + this->B) < (this->R + this->G + this->B);
}
