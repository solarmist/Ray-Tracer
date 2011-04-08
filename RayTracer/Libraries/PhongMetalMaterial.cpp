//
//  PhongMetalMaterial.cpp
//  RayTracer
//
//  Created by Joshua Olson on 4/6/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "PhongMetalMaterial.h"
#include "Texture.h"

rgb PhongMetalMaterial::ambientResponse(const ONB&, const Vector3&, const Vector3& p, const Vector2& uv){
    return R->value(uv, p);}

bool PhongMetalMaterial::specularDirection(const ONB& uvw, const Vector3& v_in, const Vector3& p, 
                                           const Vector2& uv, Vector2& seed, rgb& color, Vector3& reflection){
    precision pi = (precision)M_PI;
    precision phi = 2 * pi * seed.x();
    precision exponent = phongExp->value(uv, p).r;
    precision cosTheta = pow(1 - (precision)seed.y(), (precision)(1.0/(exponent + 1)) );
    precision sinTheta = sqrt(1 - cosTheta * cosTheta);
    precision x = sinTheta * cos(phi);
    precision y = sinTheta * sin(phi);
    precision z = cosTheta;
    
    ONB basis;
    Vector3 w = v_in - 2 * dot(v_in, uvw.w()) * uvw.w();
    basis.initFromW(w);
    
    color = R->value(uv, p);
    reflection = x * basis.u() + y * basis.v() + z * basis.w();
    
    if(exponent < 10000)
        seed.scramble();
    
    return (dot(reflection, uvw.w()) > 0);
}
