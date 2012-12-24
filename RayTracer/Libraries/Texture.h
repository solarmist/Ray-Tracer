//
//  Texture.h
//  RayTracer
//
//  Created by Joshua Olson on 3/20/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _TEXTURE_H_
#define _TEXTURE_H_ 1

#include "rgb.h"
#include "Vector2.h"
#include "Vector3.h"

class Texture {
public:
    //The Vector2 is a UV coord and the Vector3 is the 3D hit point
    virtual rgb value(const Vector2&, const Vector3&) const = 0;
};

#endif //_TEXTURE_H_