//
//  main.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/15/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#define _64_BIT 1

#ifndef precision
    //Use double on 64-bit OSs, float otherwise
    #ifdef _64_BIT
        typedef double precision;
    #else
        typedef float precision;
    #endif
#endif


#include <iostream>
#include "RNG.h"

int main (int argc, const char * argv[])
{
    RNG random;
    // insert code here...
    std::cout << "Hello, World!" << sizeof(precision) << std::endl;
    std::cout << "Hello, World!" << random() << std::endl;
    std::cout << "Hello, World!" << random() << std::endl;
    std::cout << "Hello, World!" << random() << std::endl;
        std::cout << "Hello, World!" << random() << std::endl;

    return 0;
}

