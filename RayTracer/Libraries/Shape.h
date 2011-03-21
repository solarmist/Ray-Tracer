//
//  Shape.h
//  RayTracer
//
//  Created by Joshua Olson on 3/16/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#ifndef _SHAPE_H_
#define _SHAPE_H_ 1

#include "Ray.h"
#include "rgb.h"
#include "Texture.h"
#include "Vector3.h"

class Ray;
class rgb;

struct HitRecord
{
    precision t;
    Vector3 normal;
    rgb color;
    Texture* hit_tex;
};

class Shape
{
public:
    virtual bool hit(const Ray& r, precision tmin, precision tmax, precision time, HitRecord& record) const = 0;
    virtual bool shadowHit(const Ray& r, precision tmin, precision tmax, precision time, HitRecord& record) const = 0;
};

#endif //_SHAPE_H_