//
//  Camera.h
//  RayTracer
//
//  Created by Joshua Olson on 3/18/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "ONB.h"
#include "Ray.h"

class Camera
{
public:
    Camera() {}
    Camera(const Camera& orig){
        center = orig.center;
        corner = orig.corner;
        across = orig.across;
        up = orig.up;
        uvw = orig.uvw;
        lens_radius = orig.lens_radius;
        u0 = orig.u0;
        u1 = orig.u1;
        v0 = orig.v0;
        v1 = orig.v1;
        d = orig.d;
    }
    
    Camera(Vector3 c, Vector3 gaze, Vector3 up, precision apeture, precision left,
           precision right, precision bottom, precision top, precision distance)
    :center(c), d(distance), u0(left), u1(right), v0(bottom), v1(top){
        lens_radius = apeture / 2.0f;
        uvw.initFromWV(-gaze, vup);
        corner = center + u0 * uvw.u() + v0 * uvw.v() - d * uvw.w();
        across = (u1 - u0) * uvw.u();
        up = (v1 - v0) * uvw.v();
    }
    
    //a and b are the pixel positions
    //xi1 and xi2 are the lens samples in the range (0, 1)^2
    Ray getRay(precision a, precision b, precision xi1, precision xi2){
        Vector3 origin = center + 2.0f * (xi1 - 0.5f) * lens_radius * uvw.u() +
                        2.0f * (xi2 - 0.5f) * lens_radius * uvw.v();
        Vector3 target = corner + across * a + up * b;
        return Ray(origin, unitVector(target - origin));
    }
    
    Vector3 center, corner, across, up;
    ONB uvw;
    precision lens_radius;
    precision u0, u1, v0, v1;
    precision d;
};

#endif //_CAMERA_H_