//
//  Triangle.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/16/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, const rgb& _color)
    :p0(_p0), p1(_p1), p2(_p2), color(_color){}

bool Triangle::randomPoint(const Vector3& viewPoint, const Vector2& seed, precision time, 
                 Vector3& lightPoint, Vector3& N, precision& pdf, rgb& radiance) const{
    precision temp = sqrt(1.0f - seed.x());
    precision beta = 1.0f - temp;
    precision gamma = temp * seed.y();
    lightPoint = (1.0f - beta - gamma) * p0 + beta * p1 + gamma * p2;
    
    Vector3 fromLight = unitVector(viewPoint - lightPoint);
    ONB uvw;
    N = unitVector( cross(p1 - p0, p2 - p0) );
    uvw.initFromW(N);
    
    radiance = matPtr->emittedRadiance(uvw, fromLight, lightPoint, Vector2(0,0));
    return true;
}

bool Triangle::hit(const Ray& r, precision tMin, precision tMax, precision time, HitRecord& record) const{
    precision tval;
    precision A = p0.x() - p1.x();
    precision B = p0.y() - p1.y();
    precision C = p0.z() - p1.z();
    
    precision D = p0.x() - p2.x();
    precision E = p0.y() - p2.y();
    precision F = p0.z() - p2.z();
    
    precision G = r.direction().x();
    precision H = r.direction().y();
    precision I = r.direction().z();
    
    precision J = p0.x() - r.origin().x();
    precision K = p0.y() - r.origin().y();
    precision L = p0.z() - r.origin().z();
    
    precision EIHF = E * I - H * F;
    precision GFDI = G * F - D * I;
    precision DHEG = D * H - E * G;
    
    precision denom = (A * EIHF + B * GFDI + C * DHEG);
    
    precision beta = (J * EIHF + K * GFDI + L * DHEG) / denom;
    
    if(beta <= 0.0f || beta >= 1.0f) 
        return false;
    
    precision AKJB = A * K - J * B;
    precision JCAL = J * C - A * L;
    precision BLKC = B * L - K * C;

    precision gamma = (I * AKJB + H * JCAL + G * BLKC) / denom;
    
    if(gamma <= 0.0f || beta + gamma >= 1.0f) 
        return false;
    
    tval = -(F * AKJB + E * JCAL + D * BLKC) / denom;
    
    if(tval >= tMin && tval <= tMax){
        record.t = tval;
        record.normal = unitVector(cross((p1 - p0), (p2-p0)));
        record.color = color;
        
        return true;
    }
    
    return false;
}

bool Triangle::shadowHit(const Ray& r, precision tMin, precision tMax, precision time) const{
    precision tval;
    precision A = p0.x() - p1.x();
    precision B = p0.y() - p1.y();
    precision C = p0.z() - p1.z();
    
    precision D = p0.x() - p2.x();
    precision E = p0.y() - p2.y();
    precision F = p0.z() - p2.z();
    
    precision G = r.direction().x();
    precision H = r.direction().y();
    precision I = r.direction().z();
    
    precision J = p0.x() - r.origin().x();
    precision K = p0.y() - r.origin().y();
    precision L = p0.z() - r.origin().z();
    
    precision EIHF = E * I - H * F;
    precision GFDI = G * F - D * I;
    precision DHEG = D * H - E * G;
    
    precision denom = (A * EIHF + B * GFDI + C * DHEG);
    
    precision beta = (J * EIHF + K * GFDI + L * DHEG) / denom;
    
    if(beta <= 0.0f || beta >= 1.0f) 
        return false;
    
    precision AKJB = A * K - J * B;
    precision JCAL = J * C - A * L;
    precision BLKC = B * L - K * C;
    
    precision gamma = (I * AKJB + H * JCAL + G * BLKC) / denom;
    
    if(gamma <= 0.0f || beta + gamma >= 1.0f) 
        return false;
    
    tval = -(F * AKJB + E * JCAL + D * BLKC) / denom;
    
    return (tval >= tMin && tval <= tMax);
}