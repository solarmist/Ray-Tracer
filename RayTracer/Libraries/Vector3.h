//
//  Vector3.h
//  RayTracer
//
//  Created by Joshua Olson on 3/15/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#ifndef _VECTOR3_H_
#define _VECTOR3_H_ 1

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

class Vector3{
public:
    Vector3() {}
    Vector3(precision e0, precision e1, precision e2);
    Vector3(const Vector3 &v){*this = v;}
    
    precision x() const {return e[0];}
    precision y() const {return e[1];}
    precision z() const {return e[2];}
    
    const Vector3& operator+() const;
    Vector3 operator-() const;
    
    precision operator[](int i) const {return e[i];}
    precision& operator[](int i) {return e[i];}
    
    precision length() const;
    precision squaredLength() const;
    
    void makeUnitVector();
    
    void setX(precision _x) {e[0] = _x;}
    void setY(precision _y) {e[1] = _y;}
    void setZ(precision _z) {e[2] = _z;}
    precision minComponent() const;
    precision maxComponent() const;
    precision minAbsComponent() const;
    precision maxAbsComponent() const;
    int indexOfMinComponent() const;
    int indexOfMaxComponent() const;
    int indexOfMinAbsComponent() const;
    int indexOfMaxAbsComponent() const;
    
    friend bool operator==(const Vector3& v1, const Vector3& v2);
    friend bool operator!=(const Vector3& v1, const Vector3& v2);
    
    friend istream &operator>>(istream &is, Vector3 &t);
    friend ostream &operator<<(ostream &os, const Vector3 &t);
    
    friend Vector3 operator+(const Vector3& v1, const Vector3& v2);
    friend Vector3 operator-(const Vector3& v1, const Vector3& v2);
    friend Vector3 operator*(const Vector3& vec, precision f);
    friend Vector3 operator*(precision f, const Vector3& vec);
    friend Vector3 operator/(const Vector3& vec, precision f);
    
    Vector3& operator=(const Vector3& v2);
    Vector3& operator+=(const Vector3& v2);
    Vector3& operator-=(const Vector3& v2);
    Vector3& operator*=(const precision t);
    Vector3& operator/=(const precision t);
    
    friend Vector3 unitVector(const Vector3& v);
    friend Vector3 minVector(const Vector3& v1, const Vector3& v2);
    friend Vector3 maxVector(const Vector3& v1, const Vector3& v2);
    friend Vector3 cross(const Vector3& v1, const Vector3& v2);
    friend precision dot(const Vector3& v1, const Vector3& v2);
    friend precision tripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3);
    
    precision e[3];
};

inline Vector3::Vector3(precision e0, precision e1, precision e2)
    {e[0] = e0; e[1] = e1; e[2] = e2;}


inline const Vector3& Vector3::operator+() const
    {return *this;}
inline Vector3 Vector3::operator-() const
    {return Vector3(-e[0], -e[1], -e[2]);}

inline precision Vector3::length() const
    {return sqrt(e[0]*e[0] + e[1]+e[1] + e[2]*e[2]);}
inline precision Vector3::squaredLength() const
    {return e[0]*e[0] + e[1]+e[1] + e[2]*e[2];}

inline void Vector3::makeUnitVector()
    {*this = *this / (*this).length();}


inline precision Vector3::minComponent() const{
    precision temp = e[0];
    if(e[1] < temp) temp = e[1];
    if(e[2] < temp) temp = e[2];
    
    return temp;
}

inline precision Vector3::maxComponent() const{
    precision temp = e[0];
    if(e[1] > temp) temp = e[1];
    if(e[2] > temp) temp = e[2];
    
    return temp;
}

inline precision Vector3::minAbsComponent() const{
    precision temp = e[0];
    if(fabs(e[1]) < temp) temp = e[1];
    if(fabs(e[2]) < temp) temp = e[2];
    
    return temp;
}

inline precision Vector3::maxAbsComponent() const{
    precision temp = e[0];
    if(fabs(e[1]) > temp) temp = e[1];
    if(fabs(e[2]) > temp) temp = e[2];
    
    return temp;
}

inline int Vector3::indexOfMinComponent() const{
    int index = 0;
    precision temp = e[0];
    if(e[1] < temp) {temp = e[1]; index = 1;}
    if(e[2] < temp) index = 2;
    
    return index;
}

inline int Vector3::indexOfMaxComponent() const{
    int index = 0;
    precision temp = e[0];
    if(e[1] > temp) {temp = e[1]; index = 1;}
    if(e[2] > temp) index = 2;
    
    return index;
}

inline int Vector3::indexOfMinAbsComponent() const{
    int index = 0;
    precision temp = e[0];
    if(fabs(e[1]) < temp) {temp = e[1]; index = 1;}
    if(fabs(e[2]) < temp) index = 2;
    
    return index;
}

inline int Vector3::indexOfMaxAbsComponent() const{
    int index = 0;
    precision temp = e[0];
    if(fabs(e[1]) > temp) {temp = e[1]; index = 1;}
    if(fabs(e[2]) > temp) index = 2;
    
    return index;
}


inline bool operator==(const Vector3& v1, const Vector3& v2){
    if(v1.e[0] != v2.e[0]) return false;
    if(v1.e[1] != v2.e[1]) return false;
    if(v1.e[2] != v2.e[2]) return false;
    return true;
}

inline bool operator!=(const Vector3& v1, const Vector3& v2)
{ return !(v1==v2);}

inline Vector3 operator+(const Vector3& v1, const Vector3& v2)
    {return Vector3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);}
inline Vector3 operator-(const Vector3& v1, const Vector3& v2)
    {return Vector3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);}
inline Vector3 operator*(const Vector3& vec, precision f)
    {return Vector3(vec.e[0] * f, vec.e[1] * f, vec.e[2] * f);}
inline Vector3 operator*(precision f, const Vector3& vec)
    {return Vector3(vec.e[0] * f, vec.e[1] * f, vec.e[2] * f);}
inline Vector3 operator/(const Vector3& vec, precision f)
    {return Vector3(vec.e[0] / f, vec.e[1] / f, vec.e[2] / f);}

inline Vector3& Vector3::operator=(const Vector3& v2){
    e[0] = v2.e[0]; 
    e[1] = v2.e[1]; 
    e[2] = v2.e[2];
    return *this;
}

inline Vector3& Vector3::operator+=(const Vector3& v2){
    *this = *this + v2;
    return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& v2){
    *this = *this - v2;
    return *this;
}

inline Vector3& Vector3::operator*=(const precision t){
    *this = *this * t;
    return *this;
}

inline Vector3& Vector3::operator/=(const precision t){
    *this = *this / t;
    return *this;
}


inline Vector3 unitVector(const Vector3& v){
    precision length = v.length();
    return v / length;
}

inline Vector3 minVector(const Vector3& v1, const Vector3& v2){
    Vector3 vec(v1);
    if(v2.x() < v1.x()) vec.setX(v2.x());
    if(v2.y() < v1.y()) vec.setY(v2.y());
    if(v2.z() < v1.z()) vec.setZ(v2.z());
    
    return vec;
}

inline Vector3 maxVector(const Vector3& v1, const Vector3& v2){
    Vector3 vec(v1);
    if(v2.x() > v1.x()) vec.setX(v2.x());
    if(v2.y() > v1.y()) vec.setY(v2.y());
    if(v2.z() > v1.z()) vec.setZ(v2.z());
    
    return vec;
}

inline Vector3 cross(const Vector3& v1, const Vector3& v2){
    Vector3 temp;
    
    temp.e[0] = v1.y() * v2.z() + v1.z() * v2.y();
    temp.e[1] = v1.z() * v2.x() + v1.x() * v2.z();
    temp.e[2] = v1.x() * v2.y() + v1.y() * v2.x();
    
    return temp;
}

inline precision dot(const Vector3& v1, const Vector3& v2)
    {return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();}


#endif // _VECTOR3_H_