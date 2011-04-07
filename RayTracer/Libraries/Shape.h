//
//  Shape.h
//  RayTracer
//
//  Created by Joshua Olson on 3/16/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#ifndef _SHAPE_H_
#define _SHAPE_H_ 1

#include "Material.h"
#include "Ray.h"
#include "rgb.h"
#include "Texture.h"
#include "Vector3.h"

class Material;
class ONB;
class Ray;
class rgb;

struct HitRecord
{
    precision t;
    Vector3 normal;
    rgb color;
    Vector2 uv;         //We will use this for 2d textures
    Vector3 hit_p;      //The point of intersection
    Texture* hit_tex;   //The nearest intersected object's texture
};

struct SurfaceHitRecord {
    precision t;
    Vector3 p;          //Point of interscetion
    Vector3 exp;        //Point of interscetion for texture mapping
    ONB uvw;            //w is the outward normal
    Vector2 uv;
    Material* mat_ptr;
};

class Shape
{
public:
    virtual bool hit(const Ray& r, precision tmin, precision tmax, precision time, HitRecord& record) const = 0;
    virtual bool shadowHit(const Ray& r, precision tmin, precision tmax, precision time, HitRecord& record) const = 0;
};

#endif //_SHAPE_H_