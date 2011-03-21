//
//  MarbleTexture.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/20/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "MarbleTexture.h"

rgb MarbleTexture::value(const Vector2 &uv, const Vector3 &p) const{
    precision temp = scale * noise.tubulence(freq * p, octaves);
    precision t = 2.0f * fabs(sin(freq * p.x() + temp));
    
    if (t < 1.0f)
        return (c1 * t + (1.0f - t) * c2);
    else{
        t -= 1.0f;
        return (c0 * t + (1.0f - t) * c1);
    }
}