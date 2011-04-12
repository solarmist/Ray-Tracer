//
//  Instance.cpp
//  RayTracer
//
//  Created by Joshua Olson on 4/10/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "Instance.h"

Instance::Instance(Matrix trans, Matrix transInverse, Shape* _prim)
    :M(trans), N(transInverse), prim(_prim){}

Instance::Instance(Matrix trans, Shape* _prim)
    :M(trans), N(trans), prim(_prim){N.invert();}

bool Instance::hit(const Ray& r, precision tMin, precision tMax, precision time, HitRecord& record) const{
    Vector3 nOrigin = transformLoc(N, r.origin());
    Vector3 nDir = transformVec(N, r.direction());
    Ray tRay(nOrigin, nDir);
    
    if(prim->hit(tRay, tMin, tMax, time, record)){
        record.hitP = transformLoc(M, record.hitP);
        Vector3 normal = transformVec(N.getTranspose(), record.uvw.w());
        ONB uvw;
        uvw.initFromW(normal);
        record.uvw = uvw;
        
        return true;
    }
    else
        return false;
}

bool Instance::shadowHit(const Ray& r, precision tMin, precision tMax, precision time) const{
    Vector3 nOrigin = transformLoc(N, r.origin());
    Vector3 nDir = transformVec(N, r.direction());
    Ray tRay(nOrigin, nDir);
    
    return (prim->shadowHit(tRay, tMin, tMax, time));
}
