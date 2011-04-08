//
//  Sphere.h
//  RayTracer
//
//  Created by Joshua Olson on 3/16/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#ifndef _SPHERE_H_
#define _SPHERE_H_ 1

#include "Shape.h"
#include "Vector3.h"
#include "rgb.h"
#include "Ray.h"

class Sphere : public Shape{
public:
    Sphere(const Vector3& _center, const precision _radius, const rgb& _color);
    //BBox boundingBox() const;
    bool randomPoint(const Vector3& viewPoint, const Vector2& seed, precision time, 
                     Vector3& lightPoint, Vector3& N, precision& pdf, rgb& radiance) const;
    bool hit(const Ray& r, precision tMin, precision tMax, precision time, HitRecord& record) const;
    bool shadowHit(const Ray& r, precision tMin, precision tMax, precision time, HitRecord& record) const;
    
    Vector3 center;
    precision radius;
    rgb color;
    Material* matPtr;
};

#endif //_SPHERE_H_