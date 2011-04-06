//
//  Vertex.h
//  RayTracer
//
//  Created by Joshua Olson on 4/6/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _VERTEX_H_
#define _VERTEX_H_ 1

#include "Vector2.h"
#include "Vector3.h"

struct VertexUV{
    Vector3 vertex;
    Vector2 uv;
};

struct VertexN{
    Vector3 vertex;
    Vector3 normal;
};

struct VertexUVN{
    Vector3 vertex;
    Vector3 normal;
    Vector2 uv;
};

#endif //_VERTEX_H_