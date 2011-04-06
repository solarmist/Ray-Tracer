//
//  MeshTriangleUV.h
//  RayTracer
//
//  Created by Joshua Olson on 4/6/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _MESH_TRI_H_
#define _MESH_TRI_H_ 1

#include "Mesh.h"

class MeshTriangleUV : public Shape{
public:
    MeshTriangleUV(){};
    MeshTriangleUV(Mesh* _mesh, int p0, int p1, int p2, int index)
    :mesh_ptr(_mesh) {p[0] = p0; p[1] = p1; p[2] = p2;};
    bool hit(const Ray& r, precision tmin, precision tmax, precision time, HitRecord& record) const;
    bool shadowHit(const Ray& r, precision tmin, precision tmax, precision time, HitRecord& record) const;
    
    int p[3];
    Mesh* mesh_ptr;
};

#endif //_MESH_TRI_H_