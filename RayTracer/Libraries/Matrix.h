//
//  Matrix.h
//  RayTracer
//
//  Created by Joshua Olson on 4/10/11.
//  Copyright 2011 solarmist. All rights reserved.
//
#ifndef _MATRIX_H_
#define _MATRIX_H_ 1

#include <iomanip>
#include <iostream>
#include <cmath>
#include "Vector3.h"

class Matrix {
public:
    Matrix() {}
    Matrix(const Matrix& orig);
    
    void invert();
    void transpose();
    Matrix getInverse() const;
    Matrix getTranspose() const;
    
    Matrix& operator+= (const Matrix& rightOp);
    Matrix& operator-= (const Matrix& rightOp);
    Matrix& operator*= (const Matrix& rightOp);
    Matrix& operator*= (precision rightOp);
    
    friend Matrix operator+ (const Matrix& leftOp, const Matrix& rightOp);
    friend Matrix operator- (const Matrix& leftOp, const Matrix& rightOp);
    friend Matrix operator* (const Matrix& leftOp, const Matrix& rightOp);
    friend Matrix operator* (const Matrix& leftOp, precision rightOp);
    friend Vector3 operator* (const Matrix& leftOp, const Vector3& rightOp);
    
    friend Vector3 transformLoc(const Matrix& leftOp, const Vector3& rightOp);
    friend Vector3 transformVec(const Matrix& leftOp, const Vector3& rightOp);
    
    friend Matrix zeroMatrix();
    friend Matrix identityMatrix();
    friend Matrix translate(precision x, precision y, precision z);
    friend Matrix scale(precision x, precision y, precision z);
    friend Matrix rotate(const Vector3& _axis, precision angle);
    friend Matrix rotateX(precision angle); //
    friend Matrix rotateY(precision angle); //More efficient than arbitrary axis
    friend Matrix rotateZ(precision angle); //
    friend Matrix viewMatrix(const Vector3& eye, const Vector3& gaze, const Vector3& up);
    
    friend ostream& operator<<(ostream& out, const Matrix& rightOp);
    
    precision determinant();

    precision x[4][4];
};

//3x3 matrix determinant --helper function
inline precision det3(precision a, precision b, precision c,
                      precision d, precision e, precision f,
                      precision g, precision h, precision i){
    return a*e*i + d*h*c + g*b*f - g*e*c - d*b*i - a*h*f;}

#endif //_MATRIX_H_