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
#include "Image.h"
#include "rgb.h"
#include "Sample.h"
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vector2.h"
#include "Vector3.h"
using namespace std;

int main ()
{
    HitRecord rec;
    bool is_a_hit;
    precision tmax;         //Max valid t parameter
    Vector3 dir(0, 0, -1);  //Direction of viewing rays
    const int numSamples = 100;
    Vector2 samples[numSamples];
    int height, width;
    height = 900;
    width = 1200;
    rgb background(.2f, .2f, .2f);
    
    //Geometery
    vector<Shape *> shapes;
    shapes.push_back(new Sphere(Vector3(500, 500, -2000), 
                                300, 
                                rgb(.2f, .2f, .8f)) );
    shapes.push_back(new Triangle(Vector3(600.0f, 1000.0f, -1600.0f), 
                                  Vector3(0.0f, 200.0f, -10000.0f), 
                                  Vector3(900.0f, 40.0f, -200.0f), 
                                  rgb(.8f, .2f, .2f)));
    
    Image im(width, height);
    
    multiJitter(samples, numSamples);
    
    //Loop over pixels
    for (int i = 0; i < width; i++) 
        for (int j = 0; j < height; j++) {
            rgb color(0,0,0);
            tmax = 100000.0f;
            is_a_hit = false;

            //Do all the samples for each pixel and average the color
            for (int multi = 0; multi < numSamples; multi++) {
                Ray r(Vector3(i - 0.5f +samples[multi].x(), j - 0.5f + samples[multi].y(), 0), dir);
                //Loop over list of Shapes
                for (int k = 0; k < shapes.size(); k++)
                    if(shapes[k]->hit(r, .00001f, tmax, 0.0f, rec)){
                        tmax = rec.t;
                        is_a_hit = true;
                    }
                
                if(is_a_hit)
                    color += rec.color / numSamples;
                else
                    color += background / numSamples;

            }
            im.set(i, j, color);
        }
    fstream file;
    file.open("/Users/solarmist/Documents/Graphics/RayTracer/test.ppm", fstream::out);
    im.writePPM(file);
    file.close();
    cout << "Done" << endl;
    
    return 0;
}

