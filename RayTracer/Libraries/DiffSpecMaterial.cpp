//
//  DiffSpecMaterial.cpp
//  RayTracer
//
//  Created by Joshua Olson on 4/7/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "DiffSpecMaterial.h"

rgb DiffSpecMaterial::ambientResponse(const ONB& uvw, const Vector3& v_in, const Vector3& p, const Vector2& uv){
    precision cosine = dot(v_in, uvw.w());
    if(cosine < 0.0f)
        cosine = -cosine;
    precision temp1 = 1.0f - cosine;
    precision R = R0 + (1.0f - R0) * temp1 * temp1 * temp1 * temp1 * temp1;
    precision P = (R + 0.5f) / 2.0f;
    
    if(rng() <= P)
        return specMat->ambientResponse(uvw, v_in, p, uv);
    else
        return diffMat->ambientResponse(uvw, v_in, p, uv);
}

bool DiffSpecMaterial::explicitBrdf(const ONB& uvw, const Vector3& v0, const Vector3& v1, 
                                    const Vector3& p, const Vector2& uv, rgb& brdf){
    return diffMat->explicitBrdf(uvw, v0, v1, p, uv, brdf);
}

bool DiffSpecMaterial::scatterDirection(const Vector3& v_in, const SurfaceHitRecord& rec, Vector2& seed, 
                                        rgb& color, bool& CEL, precision& brdf, Vector3& reflection){
    precision cosine = dot(v_in, rec.uvw.w());
    if(cosine < 0.0f)
        cosine = -cosine;
    precision temp1 = 1.0f - cosine;
    precision R = R0 + (1.0f - R0) * temp1 * temp1 * temp1 * temp1 * temp1;
    precision P = (R + 0.5f) / 2.0f;
    
    //We assume that spec_mat and diff_mat return brfd_scales of 1
    if(rng() <= P){
        brdf = R / P;
        return specMat->scatterDirection(v_in, rec, seed, color, CEL, brdf, reflection);
    }
    else{
        brdf = (1.0f - R) / (1.0f - P);
        return diffMat->scatterDirection(v_in, rec, seed, color, CEL, brdf, reflection);
    }
}
