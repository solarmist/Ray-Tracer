//
//  PhongMetalMaterial.h
//  RayTracer
//
//  Created by Joshua Olson on 4/6/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _PHONG_METAL_MATERIAL_H_
#define _PHONG_METAL_MATERIAL_H_ 1

#include "Material.h"

class Texture;

class PhongMetalMaterial : public Material {
public:
    PhongMetalMaterial(Texture *rt, Texture *et)
    {R = rt; phongExp = et;}
    
    rgb ambientResponse(const ONB&,        //ONB of hit point
                        const Vector3&,    //outgoing direction from light
                        const Vector3&,    //Texture point
                        const Vector2&);   //Texture coordinate
    
    bool specularDirection(const ONB&,      //ONB of hit point
                           const Vector3&,  //incident vector
                           const Vector3&,  //Texture point
                           const Vector2&,  //Texture coordinate
                           Vector2&,        //Random seed
                           rgb&,            //Value returned by texture
                           Vector3&);       //Outgoing vector
    Texture *R;
    Texture *phongExp;
};

#endif //_PHONG_METAL_MATERIAL_H_