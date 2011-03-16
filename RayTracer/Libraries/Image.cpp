//
//  Image.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/15/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include <iostream>
#include "Image.h"
using namespace std;

Image::Image()
{}

Image::Image(int width, int height){
    nx = width;
    ny = height;
    
    //Allocate memory for raster
    raster = new rgb*[nx];
    for(int i = 0; i < nx; i++)
        raster[i] = new rgb[ny];
}

Image::Image(int width, int height, rgb background){
    nx = width;
    ny = height;
    
    //Allocate memory for raster
    raster = new rgb*[nx];
    for(int i = 0; i < nx; i++){
        raster[i] = new rgb[ny];
        
        for(int j = 0; j < ny; j++)
            raster[i][j] = background;
    }
}

Image::~Image(){
    for(int i = 0; i < nx; i++)
        delete raster[i];
    
    delete raster;
}

bool Image::set(int x, int y, const rgb &color){
    //Check for out of bounds error
    if( 0 > x || x > nx) return false;
    if( 0 > y || y > ny) return false;
    
    raster[x][y] = color;
    
    return true;
}

void Image::gammaCorrect(colorPrecision gamma){
    rgb temp;
    colorPrecision power = (colorPrecision)1.0 / gamma;
    for (int i = 0; i < nx; i++) 
        for (int j = 0; j < ny; j++){
            temp = raster[i][j];
            raster[i][j] = rgb(pow(temp._r, power),
                               pow(temp._g, power),
                               pow(temp._b, power));
        }
}

void Image::writePPM(ostream &out){
    //output header
    out << "P6\n";
    out << nx << ' ' << ny << '\n';
    out << "255\n";
    int col, row;
    unsigned int ired, igreen, iblue;
    unsigned char red, green, blue;
    
    //output clamped [0, 255] values
    //Scan across the rows from bottom to top
    for(row = ny - 1 ; row >= 0; row--)
        for(col = 0 ; col < nx; col++){
            ired   = (unsigned int) (256*raster[col][row]._r);
            igreen = (unsigned int) (256*raster[col][row]._g);
            iblue  = (unsigned int) (256*raster[col][row]._b);
            
            if(ired>255)   ired   = 255;
            if(igreen>255) igreen = 255;
            if(iblue>255)  iblue  = 255;
            
            red   = (unsigned char) (ired);
            green = (unsigned char) (igreen);
            blue  = (unsigned char) (iblue);
            
            out.put(red);
            out.put(green);
            out.put(blue);
        }
}

//Reads in a binary PPM
void Image::readPPM(string file_name){
    //Open stream to file
    ifstream in;
    in.open(file_name.c_str());
    if(!in.is_open()){
        cerr << "ERROR -- Couldn't open the file \'" << file_name << "\'.\n";
        exit(-1);
    }
    
    char ch, type;
    char red, green, blue;
    int col, row, cols, rows;
    int num;
    
    //Read in header info
    in.get(ch);
    in.get(type);
    in >> cols >> rows >> num;
    
    nx = cols;
    ny = rows;
    
    //Allocate raster
    raster = new rgb*[nx];
    for (int i = 0; i < nx; i++)
        raster[i] = new rgb[ny];
    
    //Clean up newline
    in.get(ch);
    
    //Store PPM pixel values in raster
    for(row = ny - 1 ; row >= 0; row--)
        for(col = 0 ; col < nx; col++){
            in.get(red);
            in.get(green);
            in.get(blue);
            raster[col][row] = rgb( (colorPrecision)((unsigned char)red) / (colorPrecision)255.0,
                                    (colorPrecision)((unsigned char)green) / (colorPrecision)255.0,
                                    (colorPrecision)((unsigned char)blue) / (colorPrecision)255.0);
        }
}
