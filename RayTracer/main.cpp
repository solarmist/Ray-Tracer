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
#include "Camera.h"
#include "DynSphere.h"
#include "Image.h"
#include "rgb.h"
#include "RNG.h"
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
    //Camera(Vector3 center, Vector3 gaze, Vector3 vup, 
    //       precision apeture, left, right, bottom, top, distance)
    //Apeture is diameter of lens
    bool isAHit;
    RNG rng;
    precision tMax;         //Max valid t parameter
    
    //Number of samples
    const int numImage = 10;
    const int numLens = 1;
    Vector2 imageSamples[numImage], lensSamples[numLens];
    //precision minTime = 1.0f, maxTime = numSamples;


    Vector3 origin(0,0,0);
    Vector3 dir(0, 0, -1);  //Direction of viewing rays
    int nx = 800, ny = nx * 2 / 3;
    rgb background(.2f, .2f, .2f);
    
    //Camera settings
    Vector3 center(0,0,2), gaze(0,0,-2), vup(0,1,0);
    precision apeture = 2.0f;
    //Size of the film; keep height in proportion with width compared to image size
    precision width = 36, height = width * ny / nx;
    precision f = 5.6f, s = 2;
    //precision i = s * f / (s - f);
    precision u1 = width * (s - f)/(2 * f), u0 = -u1;
    precision v1 = height * (s - f)/(2 * f), v0 = -v1;
    Camera cam(center, gaze, vup,  apeture,  u0, u1,  v0,  v1,  s);

    //Geometery
    vector<Shape *> shapes;
    shapes.push_back(new Sphere(Vector3(0, 0, -2), 
                                (precision)sqrt(2), rgb(.2f, .8f, .2f)));
    shapes.push_back(new Sphere(Vector3(10, 20, -20), 
                                5, 
                                rgb(.2f, .2f, .8f)) );
    shapes.push_back(new Triangle(Vector3(300.0f, 600.0f, -200.0f), 
                                  Vector3(0.0f, 100.0f, -500.0f), 
                                  Vector3(450.0f, 20.0f, -500.0f), 
                                  rgb(.8f, .2f, .2f)));
    
    Image im(nx, ny);
    
    multiJitter(imageSamples, numImage);
    multiJitter(lensSamples, numLens);
    
    //Samples are in the range [-2,2]
    cubicSplineFilter(imageSamples, numImage);
    cubicSplineFilter(lensSamples, numLens);
    
    //Scale image samples to [-1,1]
    for (int i = 0; i < numLens; i++){
        imageSamples[i].setX( (imageSamples[i].x() + 1.0f) / 2.0f);
        imageSamples[i].setY( (imageSamples[i].y() + 1.0f) / 2.0f);
    }
    
    //Scale lens samples to [0,1]
    for (int i = 0; i < numLens; i++){
        lensSamples[i].setX( (lensSamples[i].x() + 2.0f) / 4.0f);
        lensSamples[i].setY( (lensSamples[i].y() + 2.0f) / 4.0f);
    }
    
    //Loop over pixels
    for (int x = 0; x < nx; x++) 
        for (int y = 0; y < ny; y++) {
            rgb color(0,0,0);
            tMax = 100000.0f;
            isAHit = false;

            //Do all the samples for each pixel and average the color
            for (int imageS = 0; imageS < numImage; imageS++) {
                //Project rays out into the image from the origin to the size of the viewing window
                Vector3 direction((x + 0.5f + imageSamples[imageS].x()) - (nx / 2),
                                (y + 0.5f + imageSamples[imageS].y()) - (ny / 2), 0);
                Ray r(origin, direction + nx / 10 * dir);
                //Lens samples need to be in (0,1) range.
                //Randomly pair a lens sample with a pixel sample
                //Ray r = cam.getRay((i + 0.5f + imageSamples[imageS].x()) / nx, 
                                   //(j + 0.5f + imageSamples[imageS].y()) / ny,
                                   //lensSamples[(int)(drand48() * numLens / numImage)].x(), 
                                   //lensSamples[(int)(drand48() * numLens / numImage)].y());
                //Ray r(Vector3(i + samples[multi].x(), j + samples[multi].y(), 0), dir);
                //Loop over list of Shapes
                for (int k = 0; k < shapes.size(); k++)
                    if(shapes[k]->hit(r, .00001f, tMax, 1, rec)){
                        tMax = rec.t;
                        isAHit = true;
                    }
                
                if(isAHit)
                    color += rec.color / (numImage);
                else
                    color += background / (numImage);
            }
            im.set(x, y, color);
        }
    fstream file;
    file.open("/Users/solarmist/Documents/Graphics/RayTracer/test.ppm", fstream::out);
    im.writePPM(file);
    file.close();
    cout << "Done" << endl;
    
    return 0;
}

