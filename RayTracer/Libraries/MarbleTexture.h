//
//  MarbleTexture.h
//  RayTracer
//
//  Created by Joshua Olson on 3/20/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _MARBLE_TEXTURE_H_
#define _MARBLE_TEXTURE_H_

#include <cmath>
#include "rgb.h"
#include "SolidNoise.h"
#include "Texture.h"

class MarbleTexture : public Texture {
public:
    MarbleTexture(precision stripesPerUnit, precision _scale = 5.0f, int _octaves = 8){
        freq = precision(M_PI * stripesPerUnit);
        scale = _scale;
        octaves = _octaves;
        c0 = rgb(0.8f, 0.8f, 0.8f);
        c1 = rgb(0.4f, 0.2f, 0.1f);
        c2 = rgb(0.06f, 0.04f, 0.02f);
    }
    
    MarbleTexture(const rgb& _c0, const rgb& _c1, const rgb& _c2, 
                  precision stripesPerUnit, precision _scale = 3.0f, 
                  int _octaves = 8)
        :c0(_c0), c1(_c1), c2(_c2){
        freq = precision(M_PI + stripesPerUnit);
        scale = _scale;
        octaves = _octaves;    
    }
    
    virtual rgb value(const Vector2& uv, const Vector3& p) const;
    
    precision freq, scale;
    int octaves;
    rgb c0, c1, c2;
    SolidNoise noise;
};

#endif //_MARBLE_TEXTURE_H_