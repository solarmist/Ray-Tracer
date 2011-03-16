//
//  main.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/15/11.
//  Copyright 2011 solarmist. All rights reserved.
//
//#define _64_BIT 1

#include <vector>
#include <iostream>
#include "Vector3.h"
#include "rgb.h"
#include "Image.h"
#include "Shape.h"
#include "Triangle.h"
#include "Sphere.h"
using namespace std;

int main ()
{
    HitRecord rec;
    bool is_a_hit;
    precision tmax;         //Max valid t parameter
    Vector3 dir(0, 0, -1);  //Direction of viewing rays
    int height, width;
    height = 500;
    width = 500;
    rgb background(.2f, .2f, .2f);
    
    //Geometery
    vector<Shape *> shapes;
    shapes.push_back(new Sphere(Vector3(250, 250, -1000), 
                                150, 
                                rgb(.2f, .2f, .8f)) );
    shapes.push_back(new Triangle(Vector3(300.0f, 600.0f, -800.0f), 
                                  Vector3(0.0f, 100.0f, -1000.0f), 
                                  Vector3(450.0f, 20.0f, -1000.0f), 
                                  rgb(.8f, .2f, .2f)));
    
    Image im(width, height);
    
    //Loop over pixels
    for (int i = 0; i < width; i++) 
        for (int j = 0; j < height; j++) {
            tmax = 100000.0f;
            is_a_hit = false;
            Ray r(Vector3(i, j, 0), dir);
            
            //Loop over list of Shapes
            for (int k = 0; k < shapes.size(); k++)
                if(shapes[k]->hit(r, .00001f, tmax, 0.0f, rec)){
                    tmax = rec.t;
                    is_a_hit = true;
                }
            
            if(is_a_hit)
                im.set(i, j, rec.color);
            else
                im.set(i, j, background);
        }
    fstream file;
    file.open("/Users/solarmist/Documents/Graphics/RayTracer/test.ppm", fstream::out);
    im.writePPM(cout);
    im.writePPM(file);
    file.close();
    
    return 0;
}

