#include "Color.hpp"
#include <math.h>

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

Color Color::operator+(const Color& color) {
    Color c;
    int r,g,b;
    r = this->R + color.R;
    g = this->G + color.G;
    b = this->B + color.B;
    c.R = r > 255 ? 255 : r;
    c.G = g > 255 ? 255 : g;
    c.B = b > 255 ? 255 : b;
    return c;
}
Color Color::operator+(int scalar) {
    Color c;
    int r,g,b;
    r = this->R + scalar;
    g = this->G + scalar;
    b = this->B + scalar;
    c.R = r > 255 ? 255 : r;
    c.G = g > 255 ? 255 : g;
    c.B = b > 255 ? 255 : b;
    return c;
}
Color Color::operator-(const Color& color) {
    Color c;
    int r,g,b;
    r = this->R - color.R;
    g = this->G - color.G;
    b = this->B - color.B;
    c.R = r < 0 ? 0 : r;
    c.G = g < 0 ? 0 : g;
    c.B = b < 0 ? 0 : b;
    return c;
}
Color Color::operator-(int scalar) {
    Color c;
    int r,g,b;
    r = this->R - scalar;
    g = this->G - scalar;
    b = this->B - scalar;
    c.R = r < 0 ? 0 : r;
    c.G = g < 0 ? 0 : g;
    c.B = b < 0 ? 0 : b;
    return c;
}
Color& Color::operator=(const Color& color){
    this->R = color.R;
    this->G = color.G;
    this->B = color.B;
    return *this;
}
Color Color::operator*(const Color& color) {
    Color c;
    int r,g,b;
    r = this->R * color.R;
    g = this->G * color.G;
    b = this->B * color.B;
    // clipping bawah
    r = r < 0 ? 0 : r;
    g = g < 0 ? 0 : g;
    b = b < 0 ? 0 : b;
    // clipping atas
    c.R = r > 255 ? 255 : r;
    c.G = g > 255 ? 255 : g;
    c.B = b > 255 ? 255 : b;
    return c;
}
Color Color::operator*(int scalar){
    Color c;
    int r,g,b;
    r = this->R * scalar;
    g = this->G * scalar;
    b = this->B * scalar;
    // clipping bawah
    r = r < 0 ? 0 : r;
    g = g < 0 ? 0 : g;
    b = b < 0 ? 0 : b;
    // clipping atas
    c.R = r > 255 ? 255 : r;
    c.G = g > 255 ? 255 : g;
    c.B = b > 255 ? 255 : b;
    return c;
}
Color Color::operator*(float scalar){
    Color c;
    int r,g,b;
    r = round(this->R * scalar);
    g = round(this->G * scalar);
    b = round(this->B * scalar);
    // clipping bawah
    r = r < 0 ? 0 : r;
    g = g < 0 ? 0 : g;
    b = b < 0 ? 0 : b;
    // clipping atas
    c.R = r > 255 ? 255 : r;
    c.G = g > 255 ? 255 : g;
    c.B = b > 255 ? 255 : b;
    return c;
}
Color Color::operator/(const Color& color) {
    Color c;
    int r,g,b;
    r = round(this->R / color.R);
    g = round(this->G / color.G);
    b = round(this->B / color.B);
    // clipping bawah
    r = r < 0 ? 0 : r;
    g = g < 0 ? 0 : g;
    b = b < 0 ? 0 : b;
    // clipping atas
    c.R = r > 255 ? 255 : r;
    c.G = g > 255 ? 255 : g;
    c.B = b > 255 ? 255 : b;
    return c;
}
Color Color::operator/(int scalar) {
    Color c;
    int r,g,b;
    r = round(this->R / scalar);
    g = round(this->G / scalar);
    b = round(this->B / scalar);
    // clipping bawah
    r = r < 0 ? 0 : r;
    g = g < 0 ? 0 : g;
    b = b < 0 ? 0 : b;
    // clipping atas
    c.R = r > 255 ? 255 : r;
    c.G = g > 255 ? 255 : g;
    c.B = b > 255 ? 255 : b;
    return c;
}
Color Color::operator/(float scalar) {
    Color c;
    int r,g,b;
    r = round(this->R / scalar);
    g = round(this->G / scalar);
    b = round(this->B / scalar);
    // clipping bawah
    r = r < 0 ? 0 : r;
    g = g < 0 ? 0 : g;
    b = b < 0 ? 0 : b;
    // clipping atas
    c.R = r > 255 ? 255 : r;
    c.G = g > 255 ? 255 : g;
    c.B = b > 255 ? 255 : b;
    return c;
}