//
//  DynSphere.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/18/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "DynSphere.h"

DynSphere::DynSphere(const Vector3& _ocenter, precision _radius, const rgb& _color, precision minTime, precision maxTime)
:ocenter(_ocenter), radius(_radius), color(_color), minTime(minTime), maxTime(maxTime) {}

bool DynSphere::hit(const Ray& r, precision tmin, precision tmax, precision time, HitRecord& record) const{
    Vector3 new_center = getCenter(time);
    Vector3 temp = r.origin() - new_center;
    
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
        record.normal = unitVector(r.origin() + (precision)t * r.direction() - new_center);
        record.color = color;
        
        return true;
    }
    
    return false;
}
bool DynSphere::shadowHit(const Ray& r, precision tmin, precision tmax, precision time, HitRecord& record) const{
    Vector3 new_center = getCenter(time);
    Vector3 temp = r.origin() - new_center;
    
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

Vector3 DynSphere::getCenter(precision time) const{
    precision realtime = time * maxTime + (1.0f - time) * minTime;
    return Vector3(ocenter.x() + realtime, 
                   ocenter.y() + realtime,
                   ocenter.z() + realtime);
}