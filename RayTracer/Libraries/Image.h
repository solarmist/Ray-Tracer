//
//  Image.h
//  RayTracer
//
//  Created by Joshua Olson on 3/15/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _IMAGE_H_
#define _IMAGE_H_ 1

#include <cmath>
#include <string>
#include <fstream>
#include "rgb.h"
using namespace std;

class Image{
public:
    Image();
    //Initializes rater to default rgb colo
    Image(int width, int height);
    //Initializes raster to 'background'
    Image(int width, int height, rgb background);
    ~Image();
    //return false if x or y are out of bounds, else true
    bool set(int x, int y, const rgb & color);
    void gammaCorrect(colorPrecision gamma);
    //Outputs PPM image to 'out'
    void writePPM(ostream& out);
    void readPPM(string file_name);
    
private:
    rgb** raster;
    int nx; //raster width
    int ny; //raster height
};

#endif //_IMAGE_H_