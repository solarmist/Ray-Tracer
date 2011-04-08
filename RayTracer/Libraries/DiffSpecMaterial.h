//
//  DiffSpecMaterial.h
//  RayTracer
//
//  Created by Joshua Olson on 4/7/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _DIFF_SPEC_MATERIAL_H_
#define _DIFF_SPEC_MATERIAL_H_ 1

#include "Material.h"
#include "RNG.h"
#include "Shape.h"

class DiffSpecMaterial : public Material {
public:
    DiffSpecMaterial(){}
    DiffSpecMaterial(Material *d, Material *s, precision r0 = 0.5f)
    {diffMat = d; specMat = s; R0 = r0;}
    
    rgb ambientResponse(const ONB&,        //ONB of hit point
                        const Vector3&,    //outgoing direction from light
                        const Vector3&,    //Texture point
                        const Vector2&);   //Texture coordinate
    
    bool explicitBrdf(const ONB&,      //ONB of hit point
                      const Vector3&,  //outgoing vector v0
                      const Vector3&,  //outgoing vector v1
                      const Vector3&,  //Texture point
                      const Vector2&,  //Texture coordinate
                      rgb&);           //BRDF
    
    bool scatterDirection(const Vector3&,           //incident vector
                          const SurfaceHitRecord&,  //hit we are shading
                          Vector2&,                 //Random seed
                          rgb&,                     //Color to attenuate by
                          bool&,                    //Count emitted light&
                          precision&,               //BFRD scale
                          Vector3&);                //Scattered direction
    
    precision R0;
    RNG rng;
    Material *diffMat;
    Material *specMat;
};


#endif //_DIFF_SPEC_MATERIAL_H_