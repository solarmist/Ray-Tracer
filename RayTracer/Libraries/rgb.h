//
//  rgb.h
//  RayTracer
//
//  Created by Joshua Olson on 3/15/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef rGB_H_
#define rGB_H_ 1

typedef float colorPrecision;

#include <iostream>
using namespace std;

class rgb{
    
public:
    rgb() {r = g = b = 0;}
    rgb(colorPrecision red, colorPrecision green, colorPrecision blue);
    rgb(const rgb & original) {*this = original;}
    
    void setRed(colorPrecision red)     {r = red;}
    void setGreen(colorPrecision green) {g = green;}
    void setBlue(colorPrecision blue)   {b = blue;}
    
    //colorPrecision r(){return r;}
    //colorPrecision g(){return g;}
    //colorPrecision b(){return b;}
    
    //Assignment operators
    //these operators perform no clamping
    rgb& operator=(const rgb & rightOp);
    rgb& operator+=(const rgb & rightOp);
    rgb& operator-=(const rgb & rightOp);
    rgb& operator*=(const rgb & rightOp);
    rgb& operator/=(const rgb & rightOp);
    rgb& operator*=(colorPrecision rightOp);
    rgb& operator/=(colorPrecision rightOp);
    
    //Urinary operators
    rgb operator+()const {return *this;}
    rgb operator-()const {return rgb(-r, -g, -b);}
    
    void clamp();
    
    friend ostream& operator<<(ostream & out, const rgb & theRGB);
    friend rgb operator*(const rgb & c, colorPrecision f);
    friend rgb operator*(colorPrecision f, const rgb & c);
    friend rgb operator/(const rgb & c, colorPrecision f);
    friend rgb operator*(const rgb & c1, const rgb & c2);
    friend rgb operator/(const rgb & c1, const rgb & c2);
    friend rgb operator+(const rgb & c1, const rgb & c2);
    friend rgb operator-(const rgb & c1, const rgb & c2);
    
    colorPrecision r;
    colorPrecision g;
    colorPrecision b;
};

inline rgb::rgb(colorPrecision red, colorPrecision green, colorPrecision blue)
    :r(red), g(green), b(blue) {}

inline rgb& rgb::operator+=(const rgb & rightOp){
    *this = *this + rightOp;
    return *this;
}

inline rgb& rgb::operator-=(const rgb & rightOp){
    *this = *this - rightOp;
    return *this;
}

inline rgb& rgb::operator*=(const rgb & rightOp){
    *this = *this * rightOp;
    return *this;
}

inline rgb& rgb::operator/=(const rgb & rightOp){
    *this = *this / rightOp;
    return *this;
}

inline rgb& rgb::operator*=(colorPrecision rightOp){
    *this = *this * rightOp;
    return *this;
}

inline rgb& rgb::operator/=(colorPrecision rightOp){
    *this = *this / rightOp;
    return *this;
}

inline rgb& rgb::operator=(const rgb & rightOp){
    r = rightOp.r;
    g = rightOp.g;
    b = rightOp.b;
    return *this;
}

inline void rgb::clamp(){
    if (r > 1.0f) r = 1.0f;
    if (g > 1.0f) g = 1.0f;
    if (b > 1.0f) b = 1.0f;
    if (r < 0.0f) r = 0.0f;
    if (g < 0.0f) g = 0.0f;
    if (b < 0.0f) b = 0.0f;
}

inline ostream& operator<<(ostream & out, const rgb & theRGB){
    out << theRGB.r << "r "
        << theRGB.g << "g "
        << theRGB.b << "b ";
    return out;
}

inline rgb operator*(const rgb & c, colorPrecision f)
    {return rgb(c.r * f, c.g * f, c.b * f);}

inline rgb operator*(colorPrecision f, const rgb & c)
    {return rgb(c.r * f, c.g * f, c.b * f);}

inline rgb operator/(const rgb & c, colorPrecision f)
    {return rgb(c.r / f, c.g / f, c.b / f);}

inline rgb operator*(const rgb & c1, const rgb & c2)
    {return rgb(c1.r * c2.r, c1.g / c2.g, c1.b / c2.b);}

inline rgb operator/(const rgb & c1, const rgb & c2)
    {return rgb(c1.r / c2.r, c1.g / c2.g, c1.b / c2.b);}

inline rgb operator+(const rgb & c1, const rgb & c2)
    {return rgb(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);}

inline rgb operator-(const rgb & c1, const rgb & c2)
    {return rgb(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);}

#endif // rGB_H_