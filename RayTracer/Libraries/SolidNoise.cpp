//
//  SolidNoise.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/20/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "RNG.h"
#include "SolidNoise.h"

SolidNoise::SolidNoise(){
    RNG random;
    int i;
    
    grad[0] = Vector3( 1, 1, 0);
    grad[1] = Vector3(-1, 1, 0);
    grad[2] = Vector3( 1,-1, 0);
    grad[3] = Vector3(-1,-1, 0);
    
    grad[4]  = Vector3( 1, 0, 1);
    grad[5]  = Vector3(-1, 0, 1);
    grad[6]  = Vector3( 1, 0,-1);
    grad[7]  = Vector3(-1, 0,-1);
    
    grad[8]  = Vector3( 0, 1, 1);
    grad[9]  = Vector3( 0,-1, 1);
    grad[10] = Vector3( 0, 1,-1);
    grad[11] = Vector3( 0,-1,-1);
    
    grad[12] = Vector3( 1, 1, 0);
    grad[13] = Vector3(-1, 1, 0);
    grad[14] = Vector3( 0,-1, 1);
    grad[15] = Vector3( 0,-1,-1);
    
    for (i = 0; i < 16; i++)
        phi[i] = i;
    
    for (i = 14; i >= 0; i--) {
        int target = int(random() * i);
        int temp = phi[i + 1];
        phi[i + 1] = phi[target]
        phi[target] = temp;
    }
}

precision SolidNoise::tubulence(const Vector3 &p, int depth) const{
    precision sum = 0.0f;
    precision weight = 1.0f;
    Vector3 ptemp(p);
    
    sum = fabs(noise(ptemp));
    
    for (int i = 1; i < depth; i++) {
        weight = weight * 2;
        ptemp.setX(p.x() * weight);
        ptemp.setY(p.y() * weight);
        ptemp.setZ(p.z() * weight);
        
        sum += fabs(noise(ptemp)) / weight;
    }
    return sum;
}

precision SolidNoise::dtubulence(const Vector3 &p, int depth, precision d) const{
    precision sum = 0.0f;
    precision weight = 1.0f;
    Vector3 ptemp(p);
    
    sum = fabs(noise(ptemp)) / d;
    
    for (int i = 1; i < depth; i++) {
        weight = weight * d;
        ptemp.setX(p.x() * weight);
        ptemp.setY(p.y() * weight);
        ptemp.setZ(p.z() * weight);
        
        sum += fabs(noise(ptemp)) / weight;
    }
    return sum;
}

precision SolidNoise::noise(const Vector3 &p) const{
    int fi, fj, fk;
    precision fu, fv, fw, sum;
    Vector3 v;
    
    fi = int(floor(p.x()));
    fj = int(floor(p.y()));
    fk = int(floor(p.z()));
    fu = p.x() - precision(fi);
    fv = p.y() - precision(fj);
    fw = p.z() - precision(fk);
    sum = 0.0;
    
    v = Vector3(fu, fv, fw);
    sum += knot(fi, fj, fk, v);
    
    v = Vector3(fu - 1, fv, fw);
    sum += knot(fi + 1, fj, fk, v);
    
    v = Vector3(fu, fv - 1, fw);
    sum += knot(fi, fj + 1, fk, v);
    
    v = Vector3(fu, fv, fw - 1);
    sum += knot(fi, fj, fk + 1, v);
    
    v = Vector3(fu - 1, fv - 1, fw);
    sum += knot(fi + 1, fj + 1, fk, v);
    
    v = Vector3(fu - 1, fv, fw - 1);
    sum += knot(fi + 1, fj, fk + 1, v);
    
    v = Vector3(fu, fv - 1, fw - 1);
    sum += knot(fi, fj + 1, fk + 1, v);
    
    v = Vector3(fu - 1, fv - 1, fw - 1);
    sum += knot(fi + 1, fj + 1, fk + 1, v);
    
    return sum;
}
