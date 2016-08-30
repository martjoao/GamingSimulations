#ifndef _VECTOR3_H
#define _VECTOR3_H

#include <math.h>
#include <iostream>

/*
    3-dimensional vector class
*/
class Vector3
{
public:
    //elements
    double x, y, z;

    Vector3();
    Vector3(double x, double y, double z);

    //dot and cross products
    double dot(Vector3& v);
    Vector3 cross(Vector3& v);

    //overloaded operators
    Vector3 operator+ (const Vector3& rhs);
    Vector3 operator- (const Vector3& rhs);
    Vector3 operator* (double rhs);
    Vector3 operator/ (double rhs);
    
    Vector3& operator+= (const Vector3& rhs);
    Vector3& operator-= (const Vector3& rhs);
    Vector3& operator*= (double rhs);
    Vector3& operator/= (double rhs);

    friend std::ostream& operator<< (std::ostream& os, const Vector3& v);

    //norm and normalisation methods
    Vector3 normalise();
    double norm();

};

#endif