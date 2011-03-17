//
//  Vector2.h
//  RayTracer
//
//  Created by Joshua Olson on 3/16/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#ifndef _VECTOR2_H_
#define _VECTOR2_H_ 1

#ifndef precision
    //Use double on 64-bit OSs, float otherwise
    #ifdef _64_BIT
        typedef double precision;
    #else
        typedef float precision;
    #endif
#endif

#include <cmath>
#include <iostream>
using namespace std;

class Vector2{
public:
    Vector2() {}
    Vector2(precision e0, precision e1);
    Vector2(const Vector2 &v){*this = v;}
    
    precision x() const {return e[0];}
    precision y() const {return e[1];}
    
    const Vector2& operator+() const;
    Vector2 operator-() const;
    
    precision operator[](int i) const {return e[i];}
    precision& operator[](int i) {return e[i];}
    
    precision length() const;
    precision squaredLength() const;
    
    void makeUnitVector();
    
    void setX(precision _x) {e[0] = _x;}
    void setY(precision _y) {e[1] = _y;}
    precision minComponent() const;
    precision maxComponent() const;
    precision minAbsComponent() const;
    precision maxAbsComponent() const;
    int indexOfMinComponent() const;
    int indexOfMaxComponent() const;
    int indexOfMinAbsComponent() const;
    int indexOfMaxAbsComponent() const;
    
    friend bool operator==(const Vector2& v1, const Vector2& v2);
    friend bool operator!=(const Vector2& v1, const Vector2& v2);
    
    friend istream &operator>>(istream &is, Vector2 &t);
    friend ostream &operator<<(ostream &os, const Vector2 &t);
    
    friend Vector2 operator+(const Vector2& v1, const Vector2& v2);
    friend Vector2 operator-(const Vector2& v1, const Vector2& v2);
    friend Vector2 operator*(const Vector2& vec, precision f);
    friend Vector2 operator*(precision f, const Vector2& vec);
    friend Vector2 operator/(const Vector2& vec, precision f);
    
    Vector2& operator=(const Vector2& v2);
    Vector2& operator+=(const Vector2& v2);
    Vector2& operator-=(const Vector2& v2);
    Vector2& operator*=(const precision t);
    Vector2& operator/=(const precision t);
    
    friend Vector2 unitVector(const Vector2& v);
    friend Vector2 minVector(const Vector2& v1, const Vector2& v2);
    friend Vector2 maxVector(const Vector2& v1, const Vector2& v2);
    // friend Vector2 cross(const Vector2& v1, const Vector2& v2);
    friend precision dot(const Vector2& v1, const Vector2& v2);
    // friend precision tripleProduct(const Vector2& v1, const Vector2& v2, const Vector2& v3);
    
    precision e[2];
};

inline Vector2::Vector2(precision e0, precision e1)
{e[0] = e0; e[1] = e1;}


inline const Vector2& Vector2::operator+() const
{return *this;}
inline Vector2 Vector2::operator-() const
{return Vector2(-e[0], -e[1]);}

inline precision Vector2::length() const
{return sqrt(e[0]*e[0] + e[1]+e[1]);}
inline precision Vector2::squaredLength() const
{return e[0]*e[0] + e[1]+e[1];}

inline void Vector2::makeUnitVector()
{*this = *this / (*this).length();}


inline precision Vector2::minComponent() const{
    precision temp = e[0];
    if(e[1] < temp) return e[1];
    
    return temp;
}

inline precision Vector2::maxComponent() const{
    precision temp = e[0];
    if(e[1] > temp) return e[1];

    return temp;
}

inline precision Vector2::minAbsComponent() const{
    precision temp = e[0];
    if(fabs(e[1]) < temp) return e[1];
    
    return temp;
}

inline precision Vector2::maxAbsComponent() const{
    precision temp = e[0];
    if(fabs(e[1]) > temp) return e[1];
    
    return temp;
}

inline int Vector2::indexOfMinComponent() const{
    int index = 0;
    precision temp = e[0];
    if(e[1] < temp) return 1;
    
    return index;
}

inline int Vector2::indexOfMaxComponent() const{
    int index = 0;
    precision temp = e[0];
    if(e[1] > temp) return index = 1;
    
    return index;
}

inline int Vector2::indexOfMinAbsComponent() const{
    int index = 0;
    precision temp = e[0];
    if(fabs(e[1]) < temp) return 1;
    
    return index;
}

inline int Vector2::indexOfMaxAbsComponent() const{
    int index = 0;
    precision temp = e[0];
    if(fabs(e[1]) > temp) return 1;
    
    return index;
}


inline bool operator==(const Vector2& v1, const Vector2& v2){
    if(v1.e[0] != v2.e[0]) return false;
    if(v1.e[1] != v2.e[1]) return false;
    return true;
}

inline bool operator!=(const Vector2& v1, const Vector2& v2)
{ return !(v1==v2);}

inline Vector2 operator+(const Vector2& v1, const Vector2& v2)
    {return Vector2(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1]);}
inline Vector2 operator-(const Vector2& v1, const Vector2& v2)
    {return Vector2(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1]);}
inline Vector2 operator*(const Vector2& vec, precision f)
    {return Vector2(vec.e[0] * f, vec.e[1] * f);}
inline Vector2 operator*(precision f, const Vector2& vec)
    {return Vector2(vec.e[0] * f, vec.e[1] * f);}
inline Vector2 operator/(const Vector2& vec, precision f)
    {return Vector2(vec.e[0] / f, vec.e[1] / f);}

inline Vector2& Vector2::operator=(const Vector2& v2){
    e[0] = v2.e[0]; 
    e[1] = v2.e[1]; 
    return *this;
}

inline Vector2& Vector2::operator+=(const Vector2& v2){
    *this = *this + v2;
    return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& v2){
    *this = *this - v2;
    return *this;
}

inline Vector2& Vector2::operator*=(const precision t){
    *this = *this * t;
    return *this;
}

inline Vector2& Vector2::operator/=(const precision t){
    *this = *this / t;
    return *this;
}


inline Vector2 unitVector(const Vector2& v){
    precision length = v.length();
    return v / length;
}

inline Vector2 minVector(const Vector2& v1, const Vector2& v2){
    Vector2 vec(v1);
    if(v2.x() < v1.x()) vec.setX(v2.x());
    if(v2.y() < v1.y()) vec.setY(v2.y());
    
    return vec;
}

inline Vector2 maxVector(const Vector2& v1, const Vector2& v2){
    Vector2 vec(v1);
    if(v2.x() > v1.x()) vec.setX(v2.x());
    if(v2.y() > v1.y()) vec.setY(v2.y());
    
    return vec;
}

/*inline Vector2 cross(const Vector2& v1, const Vector2& v2){
    Vector2 temp;
    
    temp.e[0] = v1.y() * v2.z() + v1.z() * v2.y();
    temp.e[1] = v1.z() * v2.x() + v1.x() * v2.z();
    temp.e[2] = v1.x() * v2.y() + v1.y() * v2.x();
    
    return temp;
}*/

inline precision dot(const Vector2& v1, const Vector2& v2)
{return v1.x() * v2.x() + v1.y() * v2.y();}

#endif // _VECTOR2_H_