#include <cmath>
#include <utility>
#include <stdexcept>
#include "vector.h"

Vector3D::Vector3D() : p({0,0,0}) {}
Vector3D::Vector3D(const Point3D& p) : p(p) {}
Vector3D::Vector3D(const Point3D& a, const Point3D& b) { this->p = {b.x - a.x, b.y - a.y, b.z - a.z}; }
Vector3D::Vector3D(float x, float y, float z) { this->p = {x, y, z}; }

Vector3D& Vector3D::operator+=(const Vector3D& vec) {
    p.x += vec->x; p.y += vec->y; p.z += vec->z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& vec) {
    p.x -= vec->x; p.y -= vec->y; p.z -= vec->z;
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D& vec) const {
    return Vector3D{p.x+vec->x, p.y+vec->y, p.z+vec->z};
}

Vector3D Vector3D::operator-(const Vector3D& vec) const {
    return Vector3D{p.x-vec->x, p.y-vec->y, p.z-vec->z};
}

float Vector3D::operator*(const Vector3D& vec) const {
    return (p.x * vec->x) + (p.y * vec->y) + (p.z * vec->z);
} 
 
Vector3D Vector3D::operator-() const { return Vector3D{-p.x, -p.y, -p.z}; }

float& Vector3D::operator[](size_t idx) {
    switch(idx) {
        case 0: return p.x;
        case 1: return p.y;
        case 2: return p.z;
        default: throw std::out_of_range("Index out of range");
    }
}

const float& Vector3D::operator[](size_t idx) const {
    switch(idx) {
        case 0: return p.x;
        case 1: return p.y;
        case 2: return p.z;
        default: throw std::out_of_range("Index out of range");
    }
}

Point3D& Vector3D::operator*() { return p; }
const Point3D& Vector3D::operator*() const { return p; }

Point3D* Vector3D::operator->() { return &p; }
const Point3D* Vector3D::operator->() const { return &p; }

void Vector3D::set_coord(Point3D q) { p = q; }
void Vector3D::set_coord(float x, float y, float z) { p.x = x; p.y = y; p.z = z; }
Point3D Vector3D::get_coord() const { return p; }
float Vector3D::length() const { return sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2)); }


Vector3D methods::sum(const Vector3D& a, const Vector3D& b) {
    return Vector3D{a->x + b->x, a->y + b->y, a->z + b->z};
}

Vector3D methods::sub(const Vector3D& a, const Vector3D& b) {
    return Vector3D{a->x - b->x, a->y - b->y, a->z - b->z};
}

Vector3D methods::mult_scalar(const Vector3D& vec, float scl) {
    return Vector3D{vec->x * scl, vec->y * scl, vec->z * scl};
}

Vector3D methods::vector_prod(const Vector3D& a, const Vector3D& b) {
    float e1 = a->y * b->z - a->z * b->y;
    float e2 = a->x * b->z - a->z * b->x;
    float e3 = a->x * b->y - a->y * b->x;
    return Vector3D{e1, e2, e3};
}

Vector3D methods::dblvector_prod(const Vector3D& a, const Vector3D& b, const Vector3D& c) {
    Vector3D vec = vector_prod(b, c);
    return vector_prod(a, vec);
}

float methods::dot_prod(const Vector3D& a, const Vector3D& b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

float methods::mixed_prod(const Vector3D& a, const Vector3D& b, const Vector3D& c) {
    return (a->x * b->y * c->z + a->y * b->z + b->x * c->y) - (c->x * b->y * a->z + b->x * a->y + c->y * b->z);
}

Vector3D methods::normalization(const Vector3D& a) {
    float length = a.length();
    return Vector3D{a->x / length, a->y / length, a->z / length};
}

float methods::angle(const Vector3D& a, const Vector3D& b) {
    float cos_angle = cos(a, b);
    if (cos_angle > 1.0) cos_angle = 1.0;
    if (cos_angle < -1.0) cos_angle = -1.0;
    return std::acos(cos_angle);
}

float methods::cos(const Vector3D& a, const Vector3D& b) {
    float scal = dot_prod(a, b);
    float lenght = a.length() * b.length();
    if (lenght == 0) return 0;
    return scal / lenght;
}

float methods::sin(const Vector3D& a, const Vector3D& b) {
    return sqrt(1 - pow(cos(a, b), 2));
}

Point3D methods::sum_points(const Point3D& a, const Point3D& b) {
    return Point3D{a.x + b.x, a.y + b.y, a.z + b.z};
}
