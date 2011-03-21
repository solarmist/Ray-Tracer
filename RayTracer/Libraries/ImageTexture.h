//
//  ImageTexture.h
//  RayTracer
//
//  Created by Joshua Olson on 3/20/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _IMAGE_TEXTURE_H_
#define _IMAGE_TEXTURE_H_ 1

#include "Texture.h"

class Image;

class ImageTexture : public Texture {
public:
    ImageTexture(char* filename);
    virtual rgb value(const Vector2& uv, const Vector3& p) const;
    
    Image* image;
};
#endif //_IMAGE_TEXTURE_H_