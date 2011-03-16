//
//  Sphere.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/16/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "Sphere.h"

Sphere::Sphere(const Vector3& _center, const precision _radius, const rgb& _color)
    :center(_center),radius(_radius),color(_color) {}

//BBox boundingBox() const;

bool Sphere::hit(const Ray& r, precision tmin, precision tmax, precision time, HitRecord& record) const{
    Vector3 temp = r.origin() - center;
    
    double a = dot(r.direction(), r.direction());
    double b = 2 * dot(r.direction(), temp);
    double c = dot(temp, temp) - radius * radius;
    
    double discriminant = b * b - 4 * a * c;
    
    //First check to see if the ray intersects the sphere
    if(discriminant > 0){
        discriminant = sqrt(discriminant);
        double t = (- b - discriminant) / (2 * a);
        
        //Now check for a valid interval
        if(t < tmin)
            t = (- b + discriminant) / (2 * a);
        if(t < tmin || t > tmax)
            return false;
        
        //We have a valid hit
        record.t = t;
        record.normal = unitVector(r.origin() + t * r.direction() - center);
        record.color = color;
        
        return true;
    }
    
    return false;
}
bool Sphere::shadowHit(const Ray& r, precision tmin, precision tmax, precision time, HitRecord& record) const{
    Vector3 temp = r.origin() - center;
    
    double a = dot(r.direction(), r.direction());
    double b = 2 * dot(r.direction(), temp);
    double c = dot(temp, temp) - radius * radius;
    
    double discriminant = b * b - 4 * a * c;
    
    //First check to see if the ray intersects the sphere
    if(discriminant > 0){
        discriminant = sqrt(discriminant);
        double t = (- b - discriminant) / (2 * a);
        
        //Now check for a valid interval
        if(t < tmin)
            t = (- b + discriminant) / (2 * a);
        if(t < tmin || t > tmax)
            return false;
        
        //We have a valid hit
        return true;
    }
    return false;
}