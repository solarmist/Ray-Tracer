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
#include "Shape.h"
#include "Vector2.h"

struct SurfaceHitRecord;

class Material {
public:
    virtual bool emits() const = 0;//{return false;}
    
    virtual rgb emittedRadiance(const ONB&,             //ONB of hit point
                                const Vector3&,         //outgoing direction from light
                                const Vector3&,         //Texture point
                                const Vector2&) = 0;    //Texture coordinate
    //{return rgb(0.0f,0.0f,0.0f);}
    
    virtual rgb ambientResponse(const ONB&,             //ONB of hit point
                                const Vector3&,         //outgoing direction from light
                                const Vector3&,         //Texture point
                                const Vector2&) = 0;    //Texture coordinate
    //{return rgb(0.0f,0.0f,0.0f);}
    
    virtual bool explicitBrdf(const ONB&,     //ONB of hit point
                              const Vector3&, //outgoing vector v0
                              const Vector3&, //outgoing vector v1
                              const Vector3&, //Texture point
                              const Vector2&, //Texture coordinate
                              rgb&) = 0;      //BRDF
    //{return false;}
    
    virtual bool diffuseDirection(const ONB&,       //ONB of hit point
                                  const Vector3&,   //incident vector
                                  const Vector3&,   //Texture point
                                  const Vector2&,   //Texture coordinate
                                  Vector2&,         //Random seed
                                  rgb&,             //Value returned by texture
                                  Vector3&) = 0;    //Reflection vector
    //{return false;}
    
    virtual bool specularDirection(const ONB&,       //ONB of hit point
                                   const Vector3&,   //incident vector
                                   const Vector3&,   //Texture point
                                   const Vector2&,   //Texture coordinate
                                   Vector2&,         //Random seed
                                   rgb&,             //Value returned by texture
                                   Vector3&) = 0;    //Reflection vector
    //{return false;}
    
    virtual bool transmissionDirection(const ONB&,      //ONB of hit point
                                       const Vector3&,  //incident unit vector
                                       const Vector3&,  //Texture point
                                       const Vector2&,  //Texture coordinate
                                       Vector2&,        //Random seed
                                       rgb&,            //extinction color
                                       precision&,      //fresnelScale
                                       Vector3&) = 0;   //Refraction vector
    //{return false;}
    
    virtual bool scatterDirection(const Vector3&,           //incident vector
                                  const SurfaceHitRecord&,  //hit we are shading
                                  Vector2&,                 //Random seed
                                  rgb&,                     //Color to attenuate by
                                  bool&,                    //Count emitted light&
                                  precision&,               //BFRD scale
                                  Vector3&) = 0;            //Reflection vector
    //{return false;}


    virtual bool isDiffuse() = 0;// {return false;}
    virtual bool isSpecular() = 0;// {return false;}
    virtual bool isTranmissive() = 0;// {return false;}
    virtual int causticPhotons() = 0;// {return 0;}
    virtual int globalPhotons() = 0;// {return 0;}
    virtual rgb photonColor() = 0;// {return rgb(0.0f, 0.0f, 0.0f);}
    
};

#endif //_MATERIAL_H_