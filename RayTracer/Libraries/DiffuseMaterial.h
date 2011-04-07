//
//  DiffuseMaterial.h
//  RayTracer
//
//  Created by Joshua Olson on 4/6/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _DIFFUSE_MATERIAL_H_
#define _DIFFUSE_MATERIAL_H_ 1

#include "Material.h"

class Texture;

class DiffuseMaterial : public Material {
public:
    DiffuseMaterial(Texture *t)
    {R = t;}
    
     virtual rgb ambientResponse(const ONB&,        //ONB of hit point
                                 const Vector3&,    //outgoing direction from light
                                 const Vector3&,    //Texture point
                                 const Vector2&);   //Texture coordinate
    
     virtual bool explicitBrdf(const ONB&,      //ONB of hit point
                               const Vector3&,  //outgoing vector v0
                               const Vector3&,  //outgoing vector v1
                               const Vector3&,  //Texture point
                               const Vector2&,  //Texture coordinate
                               rgb&);           //BRDF
    
     virtual bool diffuseDirection(const ONB&,      //ONB of hit point
                                   const Vector3&,  //incident vector
                                   const Vector3&,  //Texture point
                                   const Vector2&,  //Texture coordinate
                                   Vector2&,        //Random seed
                                   rgb&,            //Value returned by texture
                                   Vector3&);       //Outgoing vector
    Texture *R;
};

#endif //_DIFFUSE_MATERIAL_H_