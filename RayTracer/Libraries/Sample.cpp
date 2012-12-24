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

void random(Vector2* samples, int numSamples){
    for (int i = 0; i < numSamples; i++) {
        samples[i].setX((precision)drand48());
        samples[i].setY((precision)drand48());
    }
}

//Jitter assumes numSamples is a perfect square
void jitter(Vector2* samples, int numSamples){
    int sqrtSamples = (int)(sqrt(numSamples));
    for (int i = 0; i < sqrtSamples; i++) 
        for (int j = 0; j < sqrtSamples; j++) {
            precision x = (precision)(((double)i + drand48()) / (double)sqrtSamples);
            precision y = (precision)(((double)j + drand48()) / (double)sqrtSamples);
            (samples[i * sqrtSamples + j]).setX(x);
            (samples[i * sqrtSamples + j]).setY(y);
        }
}

void nrooks(Vector2* samples, int numSamples){
    for (int i = 0; i < numSamples; i++) {
        samples[i].setX(((precision)i + (precision)drand48()) / (precision)numSamples);
        samples[i].setY(((precision)i + (precision)drand48()) / (precision)numSamples);
    }
    //Shuffle the x coords
    for (int i = numSamples - 2; i >= 0; i--) {
        int target = int(drand48() * (double)i);
        precision temp = samples[i + 1].x();
        samples[i + 1].setX(samples[target].x());
        samples[target].setX(temp);
    }
}

//Multijitter assumes numSamples is a perfect square
void multiJitter(Vector2* samples, int numSamples){
    int sqrtSamples = (int)(sqrt(numSamples));
    precision subcellWidth = 1.0f / (precision(numSamples));
    
    //Initialize points to the "canonical" multi-jittered pattern
    for (int i = 0; i < sqrtSamples; i++) 
        for (int j = 0; j < sqrtSamples; j++) {
            samples[i * sqrtSamples + j].e[0] = 
                i * sqrtSamples * subcellWidth +
                j * subcellWidth + (precision)drand48() * subcellWidth;
            samples[i * sqrtSamples + j].e[1] = 
                j * sqrtSamples * subcellWidth +
                i * subcellWidth + (precision)drand48() * subcellWidth;
        }
    
    //Shuffle x coords within each column and y coords within each row
    for (int i = 0; i < sqrtSamples; i++) 
        for (int j = 0; j < sqrtSamples; j++) {
            int k = j + int(drand48() * (sqrtSamples - j - 1));
            precision t = samples[i * sqrtSamples + j].e[0];
            samples[i * sqrtSamples + j].e[0] = samples[i * sqrtSamples + k].e[0];
            samples[i * sqrtSamples + k].e[0] = t;
            
            k = j + int(drand48() * (sqrtSamples - j - 1));
            t = samples[j * sqrtSamples + i].e[1];
            samples[j * sqrtSamples + i].e[1] = samples[k * sqrtSamples + k].e[1];
            samples[k * sqrtSamples + i].e[1] = t;
        }
}

void shuffle(Vector2* samples, int numSamples){
    for (int i = numSamples - 2; i < 0; i--){
        int target = int(drand48() * (double)i);
        Vector2 temp = samples[i + 1];
        samples[i + 1] = samples[target];
        samples[target] = temp;
    }
}

void boxFilter(Vector2* samples, int numSamples){
    for (int i = 0; i < numSamples; i++){
        samples[i].setX(samples[i].x() - 0.5f);
        samples[i].setY(samples[i].y() - 0.5f);
    }
}

void tentFilter(Vector2* samples, int numSamples){
    for (int i = 0; i < numSamples; i++){
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

void cubicSplineFilter(Vector2* samples, int numSamples){
    for (int i = 0; i < numSamples; i++) {
        precision x = samples[i].x();
        precision y = samples[i].y();
        
        samples[i].e[0] = cubicFilter(x);
        samples[i].e[1] = cubicFilter(y);
    }
}

//1D sampling
void random(precision* samples, int numSamples){
    for (int i = 0; i < numSamples; i++)
        samples[i] = (precision)drand48();
}

void jitter(precision* samples, int numSamples){
    for (int i = 0; i < numSamples; i++)
        samples[i] = (precision)(((double)i + drand48()) / (double)numSamples);
}

void shuffle(precision* samples, int numSamples){
    for (int i = numSamples - 2; i >= 0; i--) {
        int target = int(drand48() * (double)i);
        precision temp = samples[i + 1];
        samples[i + 1] = samples[target];
        samples[target] = temp;
    }
}

