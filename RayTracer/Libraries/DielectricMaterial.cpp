//
//  DielectricMaterial.cpp
//  RayTracer
//
//  Created by Joshua Olson on 4/7/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "DielectricMaterial.h"

DielectricMaterial::DielectricMaterial(precision _nt, const rgb& _ex)
:nt(_nt),extinction(_ex){
    R0 = (nt - 1.0f) / (nt + 1.0f);
    R0 *= R0;
    
    colorPrecision r = log(extinction.r());
    colorPrecision g = log(extinction.g());
    colorPrecision b = log(extinction.b());
    
    extinction = rgb(r,g,b);
}

bool DielectricMaterial::specularDirection(const ONB& uvw, const Vector3& v_in, const Vector3& p, const Vector2& uv, 
                                           Vector2& seed, rgb& ratio, Vector3& reflection){
    //uvw.w() is our normal vector and -uvw.w() is the normal of the otherside of our material
    precision scale;
    precision n = 1.0f;
    precision cosine = dot(v_in, uvw.w());
    precision temp1 = 1.0f - cosine;
    precision temp2 = n / nt;
    
    if (cosine < 0.0f) {
        reflection = reflect(v_in, uvw.w());
        cosine = -cosine;
        
        //Since assuming dielectrics are embedded in air no need to 
        //check for total internal refraction here
        temp1 = 1.0f - cosine;
        scale = R0 + (1.0f - R0) * temp1 * temp1 * temp1 * temp1 * temp1;
    }
    else{   //ray is outgoing
        reflection = reflect(v_in, -uvw.w());
        cosine = -dot(v_in, -uvw.w());
        temp2 = 1 / temp2;
        precision cosinePrimeSq = 1.0f - temp2 * temp2 * (1.0f - cosine * cosine);
        
        if (cosinePrimeSq < 0.0f)
            scale = 1.0f;   //total internal refraction
        else
            scale = R0 + (1.0f - R0) * temp1 * temp1 * temp1 * temp1 * temp1;
    }
    
    //We pass back the amount of reflected light
    ratio = rgb(scale, scale, scale);
    return true;
}


bool DielectricMaterial::transmissionDirection(const ONB& uvw, const Vector3& v_in, const Vector3& p, const Vector2& uv, 
                                               Vector2& seed, rgb& _extinction, precision& fresnel_scale, Vector3& transmission){
    //uvw.w() is our normal vector and -uvw.w() is the normal of the otherside of our material
    bool value = true;
    precision n = 1.0f;
    precision cosine = dot(v_in, uvw.w());
    precision temp1 = n / nt;
    
    if (cosine < 0.0f) {
        cosine = -cosine;
        precision cosinePrimeSq = 1.0f - temp1 * temp1 * (1.0f - cosine * cosine);
        
        //Since assuming dielectrics are embedded in air no need to 
        //check for total internal refraction here
        transmission = v_in * temp1 + uvw.w() * (temp1 * cosine - sqrt(cosinePrimeSq));
        
        _extinction = rgb(1.0f, 1.0f, 1.0f);
    }
    else{   //ray is outgoing
        cosine = -dot(v_in, -uvw.w());
        temp1 =  1 / temp1;
        precision cosinePrimeSq = 1.0f - temp1 * temp1 * (1.0f - cosine * cosine);
        
        if (cosinePrimeSq < 0.0f)
            value = false;   //total internal reflection
        else{
            transmission = v_in * nt - uvw.w() * (nt * cosine - sqrt(cosinePrimeSq));    
        }
        _extinction = extinction;
    }
    
    temp1 = 1.0f - cosine;
    fresnel_scale = 1.0f - (R0 + (1.0f - R0) * temp1 * temp1 * temp1 * temp1 * temp1);
    return value;
}
