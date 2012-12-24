//
//  UVSphere.h
//  RayTracer
//
//  Created by Joshua Olson on 3/20/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _UV_SPHERE_H_
#define _UV_SPHERE_H_ 1

#include "Ray.h"
#include "Shape.h"
#include "Texture.h"
#include "Vector3.h"

class UVSphere : public Shape {
public:
    UVSphere(const Vector3& _center, const precision _radius, Texture* _tex);
    //BBox boundingBox() const;
    bool hit(const Ray& r, precision tMin, precision tMax, precision time, HitRecord& record) const;
    bool shadowHit(const Ray& r, precision tMin, precision tMax, precision time) const;
    
    Vector3 center;
    precision radius;
    Texture* tex;
};

#endif //_UV_SPHERE_H_