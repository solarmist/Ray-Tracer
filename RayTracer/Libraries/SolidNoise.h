//
//  SolidNoise.h
//  RayTracer
//
//  Created by Joshua Olson on 3/20/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _SOLID_NOISE_H_
#define _SOLID_NOISE_H_ 1

#include <math>
#include "Vector3.h"

class SolidNoise{
public:
    SolidNoise();
    precision noise(const Vector3& p) const;
    precision tubulence(const Vector3& p, int depth) const;
    precision dtubulence(const Vector3& p, int depth, precision d) const;
    precision omega(precision t) const;
    Vector3 gamma(int i, int j, int k) const;
    int intGamma(int i, int j) const;
    precision knot(int i, int j, int k) const;
    
    Vector3 grad[16];
    int phi[16];
};

inline precision SolidNoise::omega(precision t) const{
    t = (t > 0.0f) ? t : -t;
    //We can assume t is in [-1, 1] in this code so no extra 'if' needed
    return (-6.0f * t * t * t * t * t + 15.0f * t * t * t * t - 10.0f * t * t * t +1.0f);
}

inline precision SolidNoise::gamma(int i, int j, int k) const{
    int idx;
    idx = phi[abs(k) % 16];
    idx = phi[abs(j + idx) % 16];
    idx = phi[abs(i + idx) % 16];
    return grad[idx];
}

inline precision SolidNoise::knot(int i, int j, int k) const{
    const {return (omega(v.x()) * omega(v.y()) * omega(v.z()) * (dot(gamma(i, j, k), v)));}
}

inline int SolidNoise::intGamma(int i, int j) const{
    int idx;
    idx = phi[abs(j) % 16];
    idx = phi[abs(i + idx) % 16];
    return idx;
}

#endif //_SOLID_NOISE_H_