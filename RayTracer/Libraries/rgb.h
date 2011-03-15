//
//  rgb.h
//  RayTracer
//
//  Created by Joshua Olson on 3/15/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _RGB_H_
#define _RGB_H_ 1


#ifndef precision
    //Use double on 64-bit OSs, float otherwise
    #ifdef _64_BIT
        typedef double precision;
    #else
        typedef float precision;
    #endif
#endif

#ifndef colorPrecision
    //Use double on 64-bit OSs, float otherwise
    #ifdef _64_BIT
        typedef double colorPrecision;
        typedef ONE 1.0;
        typedef ZERO 0.0;
    #else
        typedef float colorPrecision;
        typedef ONE 1.0f;
        typedef ZERO 0.0f;
    #endif
#endif

#include <iostream.h>

class rgb{
    
public:
    rgb() {_r = _g = _b = 0;}
    rgb(colorPrecision red, colorPrecision green, colorPrecision blue)
    rgb(const rgb & original) {*this = original;}
    
    void setRed(colorPrecision red)     {_r = red;}
    void setGreen(colorPrecision green) {_g = green;}
    void setBlue(colorPrecision blue)   {_b = blue;}
    
    //Assignment operators
    //these operators perform no clamping
    rgb& operator=(const rgb & right_op);
    rgb& operator+=(const rgb & right_op);
    //rgb& operator-=(const rgb & right_op);
    rgb& operator*=(const rgb & right_op);
    rgb& operator/=(const rgb & right_op);
    rgb& operator*=(float right_op);
    rgb& operator/=(float right_op);
    
    //Urinary operators
    rgb operator+()const {return *this;}
    rgb operator-()const {return rgb(-_r, -_g, -_b);}
    
    void clamp();
    
    friend ostream& operator<<(ostream & out, const rgb & the_rgb);
    friend rgb operator*(const rgb & c, precision f);
    friend rgb operator*(precision f, const rgb & c);
    friend rgb operator/(const rgb & c, precision f);
    friend rgb operator*(const rgb & c, precision f);
    friend rgb operator*(const rgb & c1, const rgb & c2);
    friend rgb operator/(const rgb & c1, const rgb & c2);
    friend rgb operator+(const rgb & c1, const rgb & c2);
    
    colorPrecision _r;
    colorPrecision _g;
    colorPrecision _b;
};

inline rgb::rgb(colorPrecision red, colorPrecision green, colorPrecision blue)
    :_r(red), _g(green), _b(blue) {}

inline rgb& rgb::operator+=(const rgb & right_op){
    *this = *this + right_op;
    return *this;
}

/*inline rgb& rgb::operator-=(const rgb & right_op){
    *this = *this - right_op;
    return *this;
}*/

inline rgb& rgb::operator*=(const rgb & right_op){
    *this = *this * right_op;
    return *this;
}

inline rgb& rgb::operator/=(const rgb & right_op){
    *this = *this / right_op;
    return *this;
}

inline rgb& rgb::operator*=(colorPrecision right_op){
    *this = *this * right_op;
    return *this;
}

inline rgb& rgb::operator/=(colorPrecision right_op){
    *this = *this / right_op;
    return *this;
}

inline rgb& rgb::operator=(const rgb & right_op){
    _r = right_op._r;
    _g = right_op._g;
    _b = right_op._b;
    return *this;
}

inline void rgb::clamp(){
    if (_r > ONE) _r = ONE;
    if (_g > ONE) _g = ONE;
    if (_b > ONE) _b = ONE;
    if (_r < ZERO) _r = ZERO;
    if (_g < ZERO) _g = ZERO;
    if (_b < ZERO) _b = ZERO;
}

inline ostream& operator<<(ostream & out, const rgb & the_rgb){
    out << the_rgb._r << 'r '
        << the_rgb._g << 'g '
        << the_rgb._b << 'b ';
    return out;
}

inline rgb operator*(const rgb & c, colorPrecision f)
    {return rgb(c._r * f, c._g * f, c._b * f);}

inline rgb operator*(colorPrecision f, const rgb & c)
    {return rgb(c._r * f, c._g * f, c._b * f);}

inline rgb operator/(const rgb & c, colorPrecision f)
    {return rgb(c._r / f, c._g / f, c._b / f);}

inline rgb operator*(const rgb & c1, const rgb & c2)
    {return rgb(c1._r * c2._r, c1._g / c2._g, c1._b / c2._b);}

inline rgb operator/(const rgb & c1, const rgb & c2)
    {return rgb(c1._r / c2._r, c1._g / c2._g, c1._b / c2._b);}

inline rgb operator+(const rgb & c1, const rgb & c2)
    {return rgb(c1._r + c2._r, c1._g + c2._g, c1._b + c2._b);}


#endif // _RGB_H_