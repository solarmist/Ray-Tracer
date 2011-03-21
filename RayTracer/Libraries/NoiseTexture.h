//
//  NoiseTexture.h
//  RayTracer
//
//  Created by Joshua Olson on 3/20/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _NOISE_TEXTURE_H_
#define _NOISE_TEXTURE_H_ 1

#include <cmath>
#include "rgb.h"
#include "SolidNoise.h"
#include "Texture.h"

class NoiseTexture : public Texture {
public:
    NoiseTexture(precision _scale = 1.0f){
        scale = _scale;
        c0 = rgb(0.8f, 0.0f, 0.0f);
        c1 = rgb(0.0f, 0.0f, 0.8f);
    }
    
    NoiseTexture(const rgb& _c0, const rgb& _c1, precision _scale = 1.0f)
    :c0(_c0), c1(_c1), scale(_scale) {}
    
    virtual rgb value(const Vector2& uv, const Vector3& p) const;
    
    precision scale;
    rgb c0, c1;
    SolidNoise solid_noise;
};

#endif //_NOISE_TEXTURE_H_