//
//  DynSphere.h
//  RayTracer
//
//  Created by Joshua Olson on 3/18/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _DYN_SPHERE_H_
#define _DYN_SPHERE_H_ 1

#include "Ray.h"
#include "rgb.h"
#include "Shape.h"
#include "Vector3.h"

class DynSphere : public Shape{
public:
    DynSphere(const Vector3& _ocenter, precision _radius, const rgb& _color, precision min_time, precision max_time);
    bool hit(const Ray& r, precision tMin, precision tMax, precision time, HitRecord& record) const;
    bool shadowHit(const Ray& r, precision tMin, precision tMax, precision time) const;
    Vector3 getCenter(precision time) const;
    
    Vector3 ocenter;
    precision minTime;
    precision maxTime;
    precision radius;
    rgb color;
};

#endif //_DYN_SPHERE_H_