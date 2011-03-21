//
//  ImageTexture.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/20/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "Image.h"
#include "ImageTexture.h"

ImageTexture::ImageTexture(char * filename){
    image = new Image();
    image->readPPM(filename);
}

rgb ImageTexture::value(const Vector2 &uv, const Vector3 &p) const{
    precision u = uv.x() - int(uv.x());
    precision v = uv.y() - int(uv.y());
    u *= image->width() - 3;
    v *= image->height() - 3;
    
    int iu = (int)u;
    int iv = (int)v;
    
    precision tu = u - iu;
    precision tv = v - iv;
    
    rgb c = image->getPixel(iu    , iv    ) * (1 - tu) * (1 - tv) +
            image->getPixel(iu + 1, iv    ) *      tu  * (1 - tv) +
            image->getPixel(iu    , iv + 1) * (1 - tu) *      tv +
            image->getPixel(iu + 1, iv + 1) *      tu  *      tv;
    
    return c;
}