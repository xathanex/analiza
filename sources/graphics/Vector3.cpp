#include "Vector3.h"
#include <cmath>
#include <math.h>

Vector3::Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {}

Vector3::Vector3() {
    this->set(0.0, 0.0, 0.0);
}

void Vector3::set(float inX, float inY, float inZ) {
    this->x = inX;
    this->y = inY;
    this->z = inZ;
    
}

Vector3 Vector3::operator +(const Vector3& v) {
    return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);

}

Vector3 Vector3::operator +=(const Vector3& v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    
    return * this;

}

Vector3 Vector3::operator -(const Vector3& v) {
    return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);

}

float Vector3::getLength() {
    return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}

void Vector3::normalize() {
    float len = this->getLength();
    this->x /= len;
    this->y /= len;
    this->z /= len;
    
}

Vector3 Vector3::crossProduct(Vector3 v1, Vector3 v2) {
    
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = v1.z * v2.x - v1.x * v2.z;
    float z = v1.x * v2.y - v1.y * v2.x;
    
    return Vector3(x, y, z);
    
}

float Vector3::getEulerAngles(Vector3 v1) {
    return atan2(v1.z, v1.x) * 180 / 3.1415;
}

Vector3::~Vector3() {}

