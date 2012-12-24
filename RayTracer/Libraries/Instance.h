//
//  Instance.h
//  RayTracer
//
//  Created by Joshua Olson on 4/10/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _INSTANCE_H_
#define _INSTANCE_H_ 1

#include "Matrix.h"
#include "Shape.h"

class Matrix;

class Instance : public Shape {
public:
    Instance(){}
    Instance(Matrix trans, Matrix transInverse, Shape* _prim);
    Instance(Matrix trans, Shape* _prim);
    bool hit(const Ray& r, precision tMin, precision tMax, precision time, HitRecord& record) const;
    bool shadowHit(const Ray& r, precision tMin, precision tMax, precision time) const;

    Matrix M;
    Matrix N;
    Shape* prim;
};

#endif //_INSTANCE_H_