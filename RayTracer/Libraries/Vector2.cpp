//
//  Vector2.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/16/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "Vector2.h"

istream & operator>>(istream & is, Vector2 & t){
    precision temp;
    is >> temp;
    t.e[0] = temp;
    is >> temp;
    t.e[1] = temp;
    
    return is;
}

ostream & operator<<(ostream & os, const Vector2 & t){
    os << '('
    << t.e[0] << ' '
    << t.e[1] << ')';
    
    return os;
}

/*precision tripleProduct(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3)
{return dot((cross(v1,v2)),v3);}*/