//
//  DiffuseMaterial.cpp
//  RayTracer
//
//  Created by Joshua Olson on 4/6/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "DiffuseMaterial.h"
#include "Texture.h"

rgb DiffuseMaterial::ambientResponse(const ONB&, const Vector3&, const Vector3& p, const Vector2& uv){
    return R->value(uv, p);    
}
 
bool DiffuseMaterial::explicitBrdf(const ONB&, const Vector3&, const Vector3&, 
                                   const Vector3& p, const Vector2& uv, rgb& brdf){
    brdf = (precision)M_1_PI * R->value(uv, p); //This returned brdf by reference
    return true;
}

bool DiffuseMaterial::diffuseDirection(const ONB& uvw, const Vector3&, const Vector3& p, 
                                       const Vector2& uv, Vector2& seed, rgb& color, Vector3& reflection){
    precision pi = (precision)M_PI;
    precision phi = 2 * pi * seed.x();
    precision r = sqrt(seed.y());
    precision x = r * cos(phi);
    precision y = r * sin(phi);
    precision z = sqrt(1- x*x - y*y);
    
    color = R->value(uv, p);
    reflection = x * uvw.u() + y * uvw.v() + z * uvw.w();
    
    seed.scramble();
    return true;
}
