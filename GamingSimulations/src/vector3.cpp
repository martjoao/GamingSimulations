#include "vector3.h"

Vector3::Vector3() :x(0), y(0), z(0) {}
Vector3::Vector3(double x, double y, double z):x(x), y(y), z(z) {}

double Vector3::dot(Vector3& v)
{
    return (x * v.x + y * v.y + z * v.z);
}

Vector3 Vector3::cross(Vector3& v)
{
    return Vector3(y*v.z - z*v.y,
                   z*v.x - x*v.z,
                   x*v.y - y*v.x);
}

Vector3 Vector3::operator+ (const Vector3& rhs)
{
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3 Vector3::operator- (const Vector3& rhs)
{
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3 Vector3::operator* (double rhs)
{
    return Vector3(x * rhs, y * rhs, z * rhs);
}

Vector3 Vector3::operator/ (double rhs)
{
    return Vector3(x / rhs, y / rhs, z / rhs);
}

Vector3& Vector3::operator+= (const Vector3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector3& Vector3::operator-= (const Vector3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vector3& Vector3::operator*= (double rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

Vector3& Vector3::operator/= (double rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

std::ostream& operator<< (std::ostream& os, const Vector3& v)
{
    os << v.x << " " << v.y << " " << v.z;
    return os;
}

Vector3 Vector3::normalise()
{
    double norm = x*x + y*y + z*z;
    double invNorm = 1 / norm;
    
    return *this * sqrt(invNorm); 
}

double Vector3::norm()
{
    return sqrt(x*x + y*y + z*z);    
}