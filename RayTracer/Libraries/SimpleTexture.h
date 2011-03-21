//
//  SimpleTexture.h
//  RayTracer
//
//  Created by Joshua Olson on 3/20/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _SIMPLE_TEXTURE_H_
#define _SIMPLE_TEXTURE_H_

#include "Texture.h"

class SimpleTexture : public Texture {
public:
    SimpleTexture(rgb c) {color = c;}
    virtual rgb value(const Vector2&, const Vector3&) const {return color;}
    
    rgb color;
};
#endif //_SIMPLE_TEXTURE_H_