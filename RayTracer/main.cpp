//
//  main.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/15/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#define _64_BIT 1

#include <iostream>
#include "ONB.h"

int main (int argc, const char * argv[])
{
    Vector3 v0(0.3, 22.0, 13);
    Vector3 v1(12.3, 1.0, 98.0f);
    Vector3 v2(0.3, 1.0, 98.0f);
    Vector3 temp;
    ONB o(v0, v1, v2);
    temp = v0;
    // insert code here...
    std::cout << "Hello, World!" << v0.x()<< ' ' << v0.y() << ' '<<v0.z() << std::endl;
    std::cout << "Hello, World!" << o;

    return 0;
}

