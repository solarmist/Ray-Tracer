//
//  Material.h
//  RayTracer
//
//  Created by Joshua Olson on 4/6/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _MATERIAL_H_
#define _MATERIAL_H_ 1

#include "ONB.h"
#include "Ray.h"
#include "rgb.h"
#include "Vector2.h"

class Material {
public:
    virtual bool emits() const {return false;}
    
    virtual rgb emittedRadiance(const ONB&,     //ONB of hit point
                                const Vector3&, //outgoing direction from light
                                const Vector3&, //Texture point
                                const Vector2&) //Texture coordinate
    {return rgb(0.0f,0.0f,0.0f);}
    
    virtual rgb ambientResponse(const ONB&,     //ONB of hit point
                                const Vector3&, //outgoing direction from light
                                const Vector3&, //Texture point
                                const Vector2&) //Texture coordinate
    {return rgb(0.0f,0.0f,0.0f);}
    
    virtual bool explicitBrdf(const ONB&,     //ONB of hit point
                              const Vector3&, //outgoing vector v0
                              const Vector3&, //outgoing vector v1
                              const Vector3&, //Texture point
                              const Vector2&, //Texture coordinate
                              rgb&)           //BRDF
    {return false;}
    
    virtual bool diffuseDirection(const ONB&,       //ONB of hit point
                                  const Vector3&,   //incident vector
                                  const Vector3&,   //Texture point
                                  const Vector2&,   //Texture coordinate
                                  Vector2&,         //Random seed
                                  rgb&,             //Value returned by texture
                                  Vector3&)         //Outgoing vector
    {return false;}
    
    virtual bool specularDirection(const ONB&,       //ONB of hit point
                                  const Vector3&,   //incident vector
                                  const Vector3&,   //Texture point
                                  const Vector2&,   //Texture coordinate
                                  Vector2&,         //Random seed
                                  rgb&,             //Value returned by texture
                                  Vector3&)         //Outgoing vector
    {return false;}
    
    virtual bool transmissionDirection(const ONB&,      //ONB of hit point
                                       const Vector3&,  //incident unit vector
                                       const Vector3&,  //Texture point
                                       const Vector2&,  //Texture coordinate
                                       Vector2&,        //Random seed
                                       rgb&,            //extinction color
                                       precision&,      //fresnel_scale
                                       Vector3&)        //Outgoing vector
    {return false;}

    virtual bool isDiffuse() {return false;}
    virtual bool isSpecular() {return false;}
    virtual bool isTranmissive() {return false;}
    virtual int causticPhotons() {return 0;}
    virtual int globalPhotons() {return 0;}
    virtual rgb photonColor() {return rgb(0.0f, 0.0f, 0.0f);}
    
};

#endif //_MATERIAL_H_