//
//  Triangle.h
//  RayTracer
//
//  Created by Joshua Olson on 3/16/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_ 1

#include "Shape.h"
#include "Vector3.h"
#include "rgb.h"
#include "Ray.h"

class Triangle : public Shape{
public:
    Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, const rgb& _color);
    bool randomPoint(const Vector3& viewPoint, const Vector2& seed, precision time, 
                             Vector3& onLight, Vector3& N, precision& pdf, rgb& radiance) const;
    bool hit(const Ray& r, precision tMin, precision tMax, precision time, HitRecord& record) const;
    bool shadowHit(const Ray& r, precision tMin, precision tMax, precision time) const;
    
    Vector3 p0;
    Vector3 p1;
    Vector3 p2;
    
    rgb color;
};

#endif //_TRIANGLE_H_