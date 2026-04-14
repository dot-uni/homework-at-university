#ifndef CUBE_H
#define CUBE_H

#include "vector.h"

class Cube
{
    public:
        Cube(Point3D point, Vector3D speed, float time, float len_cube);
        Point3D run_simulation();
    private:
        void update_speed(const Vector3D& normal);
        Vector3D create_normal() const;
        float time_to_hit() const;
        void step(float time);
    private:
        Point3D point_; 
        Vector3D speed_;
        float time_;
        float len_cube_;
};

#endif