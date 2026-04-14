#ifndef VECTOR_H
#define VECTOR_H


struct Point3D
{
    float x, y, z;
};


class Vector3D
{
    public: 
        Vector3D();
        Vector3D(const Point3D& p);
        Vector3D(const Point3D& a, const Point3D& b);
        Vector3D(float x, float y, float z);

        Vector3D& operator+=(const Vector3D& vec);
        Vector3D& operator-=(const Vector3D& vec);
        Vector3D operator+(const Vector3D& vec) const;
        Vector3D operator-(const Vector3D& vec) const;
        float operator*(const Vector3D& vec) const; // dot-product
        Vector3D operator-() const;

        float& operator[](size_t idx);
        const float& operator[](size_t idx) const; 
        Point3D& operator*();
        const Point3D& operator*() const;
        Point3D* operator->();
        const Point3D* operator->() const;
    public:
        void set_coord(Point3D q);
        void set_coord(float x, float y, float z);
        Point3D get_coord() const;
        float length() const;
    private:
        Point3D p;
};


namespace methods {
    Vector3D sum(const Vector3D& a, const Vector3D& b);
    Vector3D sub(const Vector3D& a, const Vector3D& b);

    Vector3D mult_scalar(const Vector3D& vec, float scl);
    Vector3D vector_prod(const Vector3D& a, const Vector3D& b);
    Vector3D dblvector_prod(const Vector3D& a, const Vector3D& b, const Vector3D& c);
    float dot_prod(const Vector3D& a, const Vector3D& b);
    float mixed_prod(const Vector3D& a, const Vector3D& b, const Vector3D& c);

    Vector3D normalization(const Vector3D& a);

    float angle(const Vector3D& a, const Vector3D& b);
    float cos(const Vector3D& a, const Vector3D& b);
    float sin(const Vector3D& a, const Vector3D& b);

    Point3D sum_points(const Point3D& a, const Point3D& b);
}

#endif