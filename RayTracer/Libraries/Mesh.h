//
//  Mesh.h
//  RayTracer
//
//  Created by Joshua Olson on 4/6/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _MESH_H_
#define _MESH_H_ 1

#include "Shape.h"
#include "Texture.h"
#include "Vertex.h"

class Mesh{
public:
    Mesh(){}
    Texture* getTexture()const {return tex;}
    
    Texture* tex;
    Vector3* verts;
    VertexUV* vertUVs;
    VertexN* vertNS;
    VertexUVN* vertUVNS;
}

#endif //_MESH_H_
