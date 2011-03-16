//
//  Ray.h
//  RayTracer
//
//  Created by Joshua Olson on 3/16/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _RAY_H_
#define _RAY_H_

#include "Vector3.h"

class Ray{
public:
    Ray(){}
    Ray(const Vector3& a, const Vector3& b)
        {data[0] = a; data[1] = b;}
    Ray(const Ray& r)
        {*this = r;}
    Vector3 origin() const 
        {return data[0];}
    Vector3 direction() const 
        {return data[1];}
    Vector3 pointAtParameter(precision t) const
        {return data[0] + t * data[1];}
    friend ostream &operator<<(ostream &os, const Ray &r);
    
    Vector3 data[2];
};

inline ostream &operator<<(ostream &os, const Ray &r){
    os << '[' << r.origin() << " + t" << r.direction() << ']';
    return os;
}

#endif //_RAY_H_