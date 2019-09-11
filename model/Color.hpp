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
};
#endif