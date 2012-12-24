//
//  MeshTriangleUV.cpp
//  RayTracer
//
//  Created by Joshua Olson on 4/6/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "MeshTriangleUV.h"

bool MeshTriangleUV::hit(const Ray& r, precision tMin, precision tMax, precision time, HitRecord& record) const{
    Vector3 p0( (meshPtr->vertUVs[p[0]]).vertex );
    Vector3 p1( (meshPtr->vertUVs[p[1]]).vertex );
    Vector3 p2( (meshPtr->vertUVs[p[2]]).vertex );
    
    precision tVal;
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
    
    tVal = -(F * AKJB + E * JCAL + D * BLKC) / denom;
    
    if(tVal >= tMin && tVal <= tMax){
        //if prim is hit, fill record
        double alpha = 1.0 - beta - gamma;
        Vector2 u0( (meshPtr->vertUVs[p[0]]).uv );
        Vector2 u1( (meshPtr->vertUVs[p[1]]).uv );
        Vector2 u2( (meshPtr->vertUVs[p[2]]).uv );
        record.uv = Vector2((precision)(alpha * u0.x() + beta * u1.x() + gamma * u0.x()),
                            (precision)(alpha * u0.y() + beta * u1.y() + gamma * u0.y()));
        
        record.hitTex = meshPtr->getTexture();
        record.t = tVal;
        record.normal = unitVector(cross((p1 - p0), (p2-p0)));
        
        return true;
    }
    
    return false;
}

bool MeshTriangleUV::shadowHit(const Ray& r, precision tMin, precision tMax, precision time) const{
    Vector3 p0( (meshPtr->vertUVs[p[0]]).vertex );
    Vector3 p1( (meshPtr->vertUVs[p[1]]).vertex );
    Vector3 p2( (meshPtr->vertUVs[p[2]]).vertex );
    
    precision tVal;
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
    
    precision denom = A * EIHF + B * GFDI + C * DHEG;
    
    precision beta = (J * EIHF + K * GFDI + L * DHEG) / denom;
    
    if (beta <= 0.0 || beta >= 1.0) 
        return false;
        
    precision AKJB = A * K - J * B;
    precision JCAL = J * C - A * L;
    precision BLKC = B * L - K * C;
    
    precision gamma = (I * AKJB + H * JCAL + G * BLKC) / denom;
    
    if(gamma <= 0.0f || beta + gamma >= 1.0f) 
        return false;
    
    tVal = -(F * AKJB + E * JCAL + D * BLKC) / denom;

    return (tVal >= tMin && tVal <= tMax);
}
