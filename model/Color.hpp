#ifndef COLOR_HPP
#define COLOR_HPP
class Color
{
    public:
        //atribute
        unsigned char R;
        unsigned char G;
        unsigned char B;

        //constructor
        Color();

        Color(unsigned char R, unsigned char G, unsigned char B);

        //method
        void setColor(unsigned char R, unsigned char G, unsigned char B);
        bool operator==(Color& color);
        bool operator<(const Color& color) const;
        Color& operator=(const Color& color);
        Color operator+(const Color& color);
        Color operator+(int scalar);
        Color operator-(const Color& color);
        Color operator-(int scalar);
        Color operator*(const Color& color);
        Color operator*(int scalar);
        Color operator*(float scalar);
        Color operator/(const Color& color);
        Color operator/(int scalar);
        Color operator/(float scalar);
};
#endif