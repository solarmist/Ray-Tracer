//
//  NoiseTexture.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/20/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "NoiseTexture.h"

rgb NoiseTexture::value(const Vector2& uv, const Vector3& p) const{
    precision t = (1.0f + solid_noise.noise(p * scale)) / 2.0f;
    
    return t * c0 + (1.0f - t) * c1;
}