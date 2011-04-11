//
//  Sphere.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/16/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "Sphere.h"

Sphere::Sphere(const Vector3& _center, const precision _radius, const rgb& _color)
    :center(_center), radius(_radius), color(_color) {}

//BBox Sphere::boundingBox() const;

bool Sphere::randomPoint(const Vector3& viewPoint, const Vector2& seed, precision time, 
                         Vector3& lightPoint, Vector3& N, precision& pdf, rgb& radiance) const{
    precision d = (viewPoint - center).length();
    if (d < radius) 
        return false;
    
    //internal angle of cone surrounding light seen from viewpoint
    precision sinAlphaMax = radius / d;
    precision cosAlphaMax = sqrt(1 - sinAlphaMax * sinAlphaMax);
    precision q = 1 / (2 * (precision)M_PI * (1 - cosAlphaMax));
    
    precision cosAlpha = 1 + seed.x() * (cosAlphaMax - 1);
    precision sinAlpha = sqrt(1 - cosAlpha * cosAlpha);
    
    precision phi = 2 * (precision)M_PI * seed.y();
    precision cosPhi = cos(phi);
    precision sinPhi = sinf(phi);
    
    Vector3 kI(cosPhi * sinAlpha, sinPhi * sinAlpha, cosAlpha);
    
    //Construct the local coordinate system UVW where viewpoint is at
    //the origin and the sphere is at (0, 0, d) in UVW.
    ONB uvw;
    uvw.initFromW(center - viewPoint);
    Ray toLight(viewPoint, 
                kI.x() * uvw.u() + kI.y() *uvw.v() + kI.z() * uvw.w());
    
    HitRecord rec;
    if (this->hit(toLight, 0.00001f, 4294967295.0f, time, rec)) {
        lightPoint = rec.hitP;
        precision cosThetaPrime = -dot(rec.uvw.w(), toLight.direction());
        pdf = q * cosThetaPrime / (lightPoint - viewPoint).squaredLength();
        N = rec.uvw.w();
        radiance = matPtr->emittedRadiance(rec.uvw, -toLight.direction(), lightPoint, rec.uv);
        return true;
    }
    else
        return false;
}

bool Sphere::hit(const Ray& r, precision tMin, precision tMax, precision time, HitRecord& record) const{
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
        if(t < tMin)
            t = (- b + discriminant) / (2 * a);
        if(t < tMin || t > tMax)
            return false;
        
        //We have a valid hit
        record.t = (precision)t;
        record.normal = unitVector(r.origin() + (precision)t * r.direction() - center);
        record.color = color;
        
        return true;
    }
    
    return false;
}
bool Sphere::shadowHit(const Ray& r, precision tMin, precision tMax, precision time, HitRecord& record) const{
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
        if(t < tMin)
            t = (- b + discriminant) / (2 * a);
        if(t < tMin || t > tMax)
            return false;
        
        //We have a valid hit
        return true;
    }
    return false;
}