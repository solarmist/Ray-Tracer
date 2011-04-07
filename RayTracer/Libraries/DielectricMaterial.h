//
//  DielectricMaterial.h
//  RayTracer
//
//  Created by Joshua Olson on 4/7/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _DIELECTRIC_H_
#define _DIELECTRIC_H_ 1

#include "Material.h"
#include "rgb.h"
#include "Vector3.h"

class DielectricMaterial : public Material {
public:
    DielectricMaterial(){}
    DielectricMaterial(precision _nt, const rgb& _ex);
    
    virtual bool specularDirection(const ONB&,      //ONB of hit point
                                   const Vector3&,  //incident vector
                                   const Vector3&,  //Texture point
                                   const Vector2&,  //Texture coordinate
                                   Vector2&,        //Random seed
                                   rgb&,            //Value returned by texture
                                   Vector3&);       //Outgoing vector

    virtual bool transmissionDirection(const ONB&,      //ONB of hit point
                                       const Vector3&,  //incident unit vector
                                       const Vector3&,  //Texture point
                                       const Vector2&,  //Texture coordinate
                                       Vector2&,        //Random seed
                                       rgb&,            //extinction color
                                       precision&,      //fresnel_scale
                                       Vector3&);       //Outgoing vector
    
    precision R0;
    precision nt;
    rgb extinction;
};

#endif //_DIELECTRIC_H_