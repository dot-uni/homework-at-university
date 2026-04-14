#include <cmath>
#include <iostream>
#include <algorithm>
#include "vector.h"
#include "cube.h"

namespace {
    const float EPS = 1e-6f;
}

Cube::Cube(Point3D point, Vector3D speed, float time, float len_cube = 1) : point_(point), speed_(speed), time_(time), len_cube_(len_cube) {}
Point3D Cube::run_simulation() {
    float time = time_;
    while (time > 0) {
        float t_min = time_to_hit();
        if (time - t_min <= 0) {
            step(time);
        }
        else {
            step(t_min);
            Vector3D normal = create_normal();
            update_speed(normal);
        }
        time -= t_min;
    }
    return point_;
}

void Cube::update_speed(const Vector3D& normal) {
    speed_ -= methods::mult_scalar(normal, 2*(speed_ * normal));
}

void Cube::step(float time) {
    point_.x += time * speed_->x;
    point_.y += time * speed_->y;
    point_.z += time * speed_->z;
    point_.x = (point_.x < EPS) ? 0 : point_.x;
    point_.y = (point_.y < EPS) ? 0 : point_.y;
    point_.z = (point_.z < EPS) ? 0 : point_.z;
}

Vector3D Cube::create_normal() const {
    auto check = [this](float coord) {
        if (abs(coord) < EPS) return 1;
        if (abs(coord - len_cube_) < EPS) return -1;
        return 0;
    };
    float x = check(point_.x);
    float y = check(point_.y);
    float z = check(point_.z);
    Vector3D normal{x, y, z};
    return methods::normalization(normal);
}

float Cube::time_to_hit() const {
    float t_min = time_ + 1;
    for (size_t idx = 0; idx < 3; ++idx) {
        if (abs(speed_[idx]) < EPS) continue;
        float point_coord;
        switch(idx) {
            case 0: point_coord = point_.x; break;
            case 1: point_coord = point_.y; break;
            case 2: point_coord = point_.z; break;
        }
        float t = (speed_[idx] > 0) ? ((len_cube_ - point_coord) / speed_[idx]) : ((-point_coord) / speed_[idx]);
        t_min = std::min(t_min, t);
    }
    return t_min;
}
