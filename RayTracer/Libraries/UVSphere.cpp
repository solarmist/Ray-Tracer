//
//  UVSphere.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/20/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "UVSphere.h"

UVSphere::UVSphere(const Vector3& _center, const double _radius, Texture* _tex)
:center(_center), radius((precision)_radius), tex(_tex) {}

//BBox Sphere::boundingBox() const;

bool UVSphere::hit(const Ray& r, precision tmin, precision tmax, precision time, HitRecord& record) const{
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
        record.t = (precision)t;
        record.hit_p = (r.origin() + (precision)t * r.direction());
        //record.normal = unitVector(r.origin() + (precision)t * r.direction() - center);
        Vector3 n = record.normal = (record.hit_p - center) / radius;
        
        //Calculate UV coordinates
        precision twopi = precision(2 * M_PI);
        precision one_over_2pi = precision(M_1_PI / 2) ;
        precision theta = acos(n.z());
        precision phi   = atan2(n.y(), n.x());
        if (phi < 0.0f)
            phi += twopi;
        
        record.uv = Vector2(precision(phi * one_over_2pi), precision((M_PI - theta) * M_1_PI));
        return true;
    }
    
    return false;
}
bool UVSphere::shadowHit(const Ray& r, precision tmin, precision tmax, precision time, HitRecord& record) const{
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