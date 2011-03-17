//
//  Sample.cpp
//  RayTracer
//
//  Created by Joshua Olson on 3/16/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include <cmath>
#include <cstdlib>
#include "Sample.h"
#include "Vector2.h"

void random(Vector2* samples, int num_samples){
    for (int i = 0; i < num_samples; i++) {
        samples[i].setX((precision)drand48());
        samples[i].setY((precision)drand48());
    }
}

//Jitter assumes num_samples is a perfect square
void jitter(Vector2* samples, int num_samples){
    int sqrt_samples = (int)(sqrt(num_samples));
    for (int i = 0; i < sqrt_samples; i++) 
        for (int j = 0; j < sqrt_samples; j++) {
            precision x = (precision)(((double)i + drand48()) / (double)sqrt_samples);
            precision y = (precision)(((double)j + drand48()) / (double)sqrt_samples);
            (samples[i * sqrt_samples + j]).setX(x);
            (samples[i * sqrt_samples + j]).setY(y);
        }
}

void nrooks(Vector2* samples, int num_samples){
    for (int i = 0; i < num_samples; i++) {
        samples[i].setX(((precision)i + (precision)drand48()) / (precision)num_samples);
        samples[i].setY(((precision)i + (precision)drand48()) / (precision)num_samples);
    }
    //Shuffle the x coords
    for (int i = num_samples - 2; i >= 0; i--) {
        int target = int(drand48() * (double)i);
        precision temp = samples[i + 1].x();
        samples[i + 1].setX(samples[target].x());
        samples[target].setX(temp);
    }
}
//Multijitter assumes num_samples is a perfect square
void multiJitter(Vector2* samples, int num_samples){
    int sqrt_samples = (int)(sqrt(num_samples));
    precision subcell_width = 1.0f / (precision(num_samples));
    
    //Initialize points to the "canonical" multi-jittered pattern
    for (int i = 0; i < sqrt_samples; i++) 
        for (int j = 0; j < sqrt_samples; j++) {
            samples[i * sqrt_samples + j].e[0] = 
                i * sqrt_samples * subcell_width +
                j * subcell_width + (precision)drand48() * subcell_width;
            samples[i * sqrt_samples + j].e[1] = 
                j * sqrt_samples * subcell_width +
                i * subcell_width + (precision)drand48() * subcell_width;
        }
    
    //Shuffle x coords within each column and y coords within each row
    for (int i = 0; i < sqrt_samples; i++) 
        for (int j = 0; j < sqrt_samples; j++) {
            int k = j + int(drand48() * (sqrt_samples - j - 1));
            precision t = samples[i * sqrt_samples + j].e[0];
            samples[i * sqrt_samples + j].e[0] = samples[i * sqrt_samples + k].e[0];
            samples[i * sqrt_samples + k].e[0] = t;
            
            k = j + int(drand48() * (sqrt_samples - j - 1));
            t = samples[j * sqrt_samples + i].e[1];
            samples[j * sqrt_samples + i].e[1] = samples[k * sqrt_samples + k].e[1];
            samples[k * sqrt_samples + i].e[1] = t;
        }
}
void shuffle(Vector2* samples, int num_samples){
    for (int i = num_samples - 2; i < 0; i--){
        int target = int(drand48() * (double)i);
        Vector2 temp = samples[i + 1];
        samples[i + 1] = samples[target];
        samples[target] = temp;
    }
}

void boxFilter(Vector2* samples, int num_samples){
    for (int i = 0; i < num_samples; i++){
        samples[i].setX(samples[i].x() - 0.5f);
        samples[i].setY(samples[i].y() - 0.5f);
    }
}
void tentFilter(Vector2* samples, int num_samples){
    for (int i = 0; i < num_samples; i++){
        precision x = samples[i].x();
        precision y = samples[i].y();
        
        if(x < 0.5f) 
            samples[i].setX((precision)sqrt(2.0 * (double)x) - 1.0f);
        else
            samples[i].setX(1.0f - (precision)sqrt(2.0 - 2.0 * (double)x));
        
        if(y < 0.5f) 
            samples[i].setY((precision)sqrt(2.0 * (double)y) - 1.0f);
        else
            samples[i].setY(1.0f - (precision)sqrt(2.0 - 2.0 * (double)y));
    }
}
void cubicSplineFilter(Vector2* samples, int num_samples){
    for (int i = 0; i < num_samples; i++) {
        precision x = samples[i].x();
        precision y = samples[i].y();
        
        samples[i].e[0] = cubicFilter(x);
        samples[i].e[1] = cubicFilter(y);
    }
}

//1D sampling
void random(precision* samples, int num_samples){
    for (int i = 0; i < num_samples; i++)
        samples[i] = (precision)drand48();
}
void jitter(precision* samples, int num_samples){
    for (int i = 0; i < num_samples; i++)
        samples[i] = (precision)(((double)i + drand48()) / (double)num_samples);
}
void shuffle(precision* samples, int num_samples){
    for (int i = num_samples - 2; i >= 0; i--) {
        int target = int(drand48() * (double)i);
        precision temp = samples[i + 1];
        samples[i + 1] = samples[target];
        samples[target] = temp;
    }
}

