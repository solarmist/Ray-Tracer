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

/*struct HitRecord
{
    precision t;
    Vector3 normal;
    rgb color;
    Vector2 uv;         //We will use this for 2d textures
    Vector3 hitP;      //The point of intersection
    Texture* hitTex;   //The nearest intersected object's texture
};//*/

//SurfaceHitRecord
struct HitRecord {
    precision t;

    //From old version
    Vector3 normal;
    rgb color;
    Texture* hitTex;   //The nearest intersected object's texture

    Vector3 hitP;          //Point of interscetion
    Vector3 exp;        //Point of interscetion for texture mapping
    ONB uvw;            //w is the outward normal
    Vector2 uv;
    Material* matPtr;
};

class Shape
{
public:
    virtual bool randomPoint(const Vector3& viewPoint, const Vector2& seed, precision time, 
                     Vector3& lightPoint, Vector3& N, precision& pdf, rgb& radiance) const = 0;
    virtual bool hit(const Ray& r, precision tMin, precision tMax, precision time, HitRecord& record) const = 0;
    virtual bool shadowHit(const Ray& r, precision tMin, precision tMax, precision time) const = 0;
    
    Material* matPtr;
};

#endif //_SHAPE_H_