//
//  Vector3.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/15/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "Vector3.h"

istream & operator>>(istream &is, Vector3 &t){
    precision temp;
    is >> temp;
    t.e[0] = temp;
    is >> temp;
    t.e[1] = temp;
    is >> temp;
    t.e[2] = temp;
    
    return is;
}

ostream & operator<<(ostream &os, Vector3 &t){
    os << '('
        << t.e[0] << ' '
        << t.e[1] << ' '
        << t.e[2] << ')';
    
    return os;
}

precision tripleProduct(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3)
    {return dot((cross(v1,v2)),v3);}