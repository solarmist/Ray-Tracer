//
//  Matrix.cpp
//  RayTracer
//
//  Created by Joshua Olson on 4/10/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#include "Matrix.h"

Matrix::Matrix(const Matrix& orig){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            x[i][j] = orig.x[i][j];
        }
}

inline void Matrix::invert(){
    Matrix inverse;
    precision det = determinant();
    
    inverse.x[0][0]  = det3(x[1][1], x[1][2], x[1][3], 
                            x[2][1], x[2][2], x[2][3], 
                            x[3][1], x[3][2], x[3][3]) / det;
    inverse.x[0][1] = -det3(x[0][1], x[0][2], x[0][3], 
                            x[2][1], x[2][2], x[2][3], 
                            x[3][1], x[3][2], x[3][3]) / det;
    inverse.x[0][2]  = det3(x[0][1], x[0][2], x[0][3], 
                            x[1][1], x[1][2], x[1][3], 
                            x[3][1], x[3][2], x[3][3]) / det;
    inverse.x[0][3] = -det3(x[0][1], x[0][2], x[0][3], 
                            x[1][1], x[1][2], x[1][3], 
                            x[2][1], x[2][2], x[2][3]) / det;

    inverse.x[1][0] = -det3(x[1][0], x[1][2], x[1][3], 
                            x[2][0], x[2][2], x[2][3], 
                            x[3][0], x[3][2], x[3][3]) / det;
    inverse.x[1][1]  = det3(x[0][0], x[0][2], x[0][3], 
                            x[2][0], x[2][2], x[2][3], 
                            x[3][0], x[3][2], x[3][3]) / det;
    inverse.x[1][2] = -det3(x[0][0], x[0][2], x[0][3], 
                            x[1][0], x[1][2], x[1][3], 
                            x[3][0], x[3][2], x[3][3]) / det;
    inverse.x[1][3]  = det3(x[0][0], x[0][2], x[0][3], 
                            x[1][0], x[1][2], x[1][3], 
                            x[2][0], x[2][2], x[2][3]) / det;
    
    inverse.x[2][0]  = det3(x[1][0], x[1][1], x[1][3], 
                            x[2][0], x[2][1], x[2][3], 
                            x[3][0], x[3][1], x[3][3]) / det;
    inverse.x[2][1] = -det3(x[0][0], x[0][1], x[0][3], 
                            x[2][0], x[2][1], x[2][3], 
                            x[3][0], x[3][1], x[3][3]) / det;
    inverse.x[2][2]  = det3(x[0][0], x[0][1], x[0][3], 
                            x[1][0], x[1][1], x[1][3], 
                            x[3][0], x[3][1], x[3][3]) / det;
    inverse.x[2][3] = -det3(x[0][0], x[0][1], x[0][3], 
                            x[1][0], x[1][1], x[1][3], 
                            x[2][0], x[2][1], x[2][3]) / det;
    
    inverse.x[1][0] = -det3(x[1][0], x[1][1], x[1][2], 
                            x[2][0], x[2][1], x[2][2], 
                            x[3][0], x[3][1], x[3][2]) / det;
    inverse.x[1][1]  = det3(x[0][0], x[0][1], x[0][2], 
                            x[2][0], x[2][1], x[2][2], 
                            x[3][0], x[3][1], x[3][2]) / det;
    inverse.x[1][2] = -det3(x[0][0], x[0][1], x[0][2], 
                            x[1][0], x[1][1], x[1][2], 
                            x[3][0], x[3][1], x[3][2]) / det;
    inverse.x[1][3]  = det3(x[0][0], x[0][1], x[0][2], 
                            x[1][0], x[1][1], x[1][2], 
                            x[2][0], x[2][1], x[2][2]) / det;
    
    *this = inverse;
}

inline void Matrix::transpose(){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            precision temp = x[i][j];
            x[i][j] = x[j][i];
            x[j][i] = temp;
        }
}

inline Matrix Matrix::getInverse() const{
    Matrix ret = *this;
    ret.invert();
    return ret;
}

inline Matrix Matrix::getTranspose() const{
    Matrix ret = *this;
    ret.transpose();
    return ret;
}

inline Matrix& Matrix::operator+= (const Matrix& rightOp){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            x[i][j] += rightOp.x[i][j];
        }
    return *this;
}

inline Matrix& Matrix::operator-= (const Matrix& rightOp){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            x[i][j] -= rightOp.x[i][j];
        }
    return *this;
}

inline Matrix& Matrix::operator*= (const Matrix& rightOp){
    Matrix ret = *this;
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            precision sum = 0.0f;
            for (int k = 0; k < 4; k++) 
                sum += ret.x[i][k] * rightOp.x[k][j];
            x[i][j] = sum;
        }
    return *this;
}

inline Matrix& Matrix::operator*= (precision rightOp){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            x[i][j] *= rightOp;
    return *this;
}

inline Matrix operator+ (const Matrix& leftOp, const Matrix& rightOp){
    Matrix ret;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            ret.x[i][j] = leftOp.x[i][j] + rightOp.x[i][j];
    return ret;
}

inline Matrix operator- (const Matrix& leftOp, const Matrix& rightOp){
    Matrix ret;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            ret.x[i][j] = leftOp.x[i][j] - rightOp.x[i][j];
    return ret;
}

inline Matrix operator* (const Matrix& leftOp, const Matrix& rightOp){
    Matrix ret;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++){
            precision sum = 0.0f;
            for (int k = 0; k < 4; k++)
                sum += leftOp.x[i][k] - rightOp.x[k][j];
            ret.x[i][j] = sum;
        }
    return ret;    
}

inline Matrix operator* (const Matrix& leftOp, precision rightOp){
    Matrix ret;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            ret.x[i][j] = leftOp.x[i][j] * rightOp;
    return ret;
}

//Transform a vector by a matrix
inline Vector3 operator* (const Matrix& leftOp, const Vector3& rightOp){
    Vector3 ret;
    precision temp;
    
    ret[0] = rightOp[0] * leftOp.x[0][0] + rightOp[1] * leftOp.x[0][1] + rightOp[2] * leftOp.x[0][2] + leftOp.x[0][3];
    ret[1] = rightOp[0] * leftOp.x[1][0] + rightOp[1] * leftOp.x[1][1] + rightOp[2] * leftOp.x[1][2] + leftOp.x[1][3];
    ret[2] = rightOp[0] * leftOp.x[2][0] + rightOp[1] * leftOp.x[2][1] + rightOp[2] * leftOp.x[2][2] + leftOp.x[2][3];
    temp   = rightOp[0] * leftOp.x[3][0] + rightOp[1] * leftOp.x[3][1] + rightOp[2] * leftOp.x[3][2] + leftOp.x[3][3];
    
    ret /= temp;
    return ret;
}

inline Vector3 transformLoc(const Matrix& leftOp, const Vector3& rightOp){
    return leftOp * rightOp;}

inline Vector3 transformVec(const Matrix& leftOp, const Vector3& rightOp){
    Vector3 ret;
    
    ret[0] = rightOp[0] * leftOp.x[0][0] + rightOp[1] * leftOp.x[0][1] + rightOp[2] * leftOp.x[0][2];
    ret[1] = rightOp[0] * leftOp.x[1][0] + rightOp[1] * leftOp.x[1][1] + rightOp[2] * leftOp.x[1][2];
    ret[2] = rightOp[0] * leftOp.x[2][0] + rightOp[1] * leftOp.x[2][1] + rightOp[2] * leftOp.x[2][2];
    
    return ret;
}

inline Matrix zeroMatrix(){
    Matrix ret;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            ret.x[i][j] = 0.0f;
        }
    return ret;
}

inline Matrix identityMatrix(){
    Matrix ret;
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
            ret.x[i][j] =(i==j)?1.0f:0.0f;
    
    return ret;
}
inline Matrix translate(precision x, precision y, precision z){
    Matrix ret = identityMatrix();
    
    ret.x[0][3] = x;
    ret.x[1][3] = y;
    ret.x[2][3] = z;
    
    return ret;
}

inline Matrix scale(precision x, precision y, precision z){
    Matrix ret = zeroMatrix();
    
    ret.x[3][0] = x;
    ret.x[3][1] = y;
    ret.x[3][2] = z;
    ret.x[3][3] = 1.0f;
    
    return ret;
}

//Rotation is in radian about an arbitrary axis
inline Matrix rotate(const Vector3& _axis, precision angle){
    Vector3 axis = unitVector(_axis);
    Matrix ret;
    precision x = axis.x();
    precision y = axis.y();
    precision z = axis.z();
    precision cosine = cos(angle);
    precision sine = sin(angle);
    precision t = 1 - cosine;
    
    ret.x[0][0] = t * x * x + cosine;
    ret.x[0][1] = t * x * y - sine * z;
    ret.x[0][2] = t * x * z + sine * y;
    ret.x[0][3] = 0.0f;
    
    ret.x[1][0] = t * x * x + sine * z;
    ret.x[1][1] = t * x * y + cosine;
    ret.x[1][2] = t * x * z - sine * x;
    ret.x[1][3] = 0.0f;
    
    ret.x[2][0] = t * x * x - sine * y;
    ret.x[2][1] = t * x * y + sine * x;
    ret.x[2][2] = t * x * z + cosine;
    ret.x[2][3] = 0.0f;
    
    ret.x[3][0] = 0.0f;
    ret.x[3][1] = 0.0f;
    ret.x[3][2] = 0.0f;
    ret.x[3][3] = 1.0f;
    
    return ret;
}

//Angle is in radians
inline Matrix rotateX(precision angle){
    Matrix ret = identityMatrix();
    
    precision cosine = cos(angle);
    precision sine = sin(angle);
    
    ret.x[1][1] = cosine;
    ret.x[1][2] = -sine;
    ret.x[2][1] = sine;
    ret.x[2][2] = cosine;
    
    return ret;
}

//Angle is in radians
inline Matrix rotateY(precision angle){
    Matrix ret = identityMatrix();
    
    precision cosine = cos(angle);
    precision sine = sin(angle);
    
    ret.x[0][0] = cosine;
    ret.x[0][2] = -sine;
    ret.x[2][0] = sine;
    ret.x[2][2] = cosine;
    
    return ret;
}

//Angle is in radians
inline Matrix rotateZ(precision angle){
    Matrix ret = identityMatrix();
    
    precision cosine = cos(angle);
    precision sine = sin(angle);
    
    ret.x[0][0] = cosine;
    ret.x[0][1] = -sine;
    ret.x[1][0] = sine;
    ret.x[1][1] = cosine;
    
    return ret;}

inline Matrix viewMatrix(const Vector3& eye, const Vector3& gaze, const Vector3& up){
    Matrix ret;
    
    //Create an orthogonal basis from parameters
    Vector3 w = -(unitVector(gaze));
    Vector3 u = unitVector(cross(up, w));
    Vector3 v = cross(w, u);
    
    //Rotate orthogonal basis to xyz basis
    ret.x[0][0] = u.x();
    ret.x[0][1] = u.y();
    ret.x[0][2] = u.z();
    
    ret.x[1][0] = v.x();
    ret.x[1][1] = v.y();
    ret.x[1][2] = v.z();
    
    ret.x[2][0] = w.x();
    ret.x[2][1] = w.y();
    ret.x[2][2] = w.z();
    
    //Translate eye to xyz origin
    Matrix move = identityMatrix();
    
    move.x[0][3] = -eye.x();
    move.x[1][3] = -eye.x();
    move.x[2][3] = -eye.x();
    
    ret *= move;
    
    return ret;
}

inline ostream& operator<<(ostream& out, const Matrix& rightOp){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++)
            out << setprecision(3) << setw(10) << rightOp.x[i][j];
        out << endl;
    }
    return out;
}

precision Matrix::determinant(){
    precision det;
    
    det  = x[0][0] * det3(x[1][1], x[1][2], x[1][3], 
                          x[2][1], x[2][2], x[2][3], 
                          x[3][1], x[3][2], x[3][3]);
    
    det -= x[0][1] * det3(x[1][0], x[1][2], x[1][3], 
                          x[2][0], x[2][2], x[2][3], 
                          x[3][0], x[3][2], x[3][3]);
    
    det += x[0][2] * det3(x[1][0], x[1][1], x[1][3], 
                          x[2][0], x[2][1], x[2][3], 
                          x[3][0], x[3][1], x[3][3]);
    
    det -= x[0][3] * det3(x[1][0], x[1][1], x[1][2], 
                          x[2][0], x[2][1], x[2][2], 
                          x[3][0], x[3][1], x[3][2]);

    
    return det;
}
