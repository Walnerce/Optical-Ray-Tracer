#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class Vec3 {
public:
    double e[3];

    Vec3() : e{0,0,0} {}
    Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vec3 operator+(const Vec3 &v) const {
        return Vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
    }
    
    Vec3 operator*(double t) const {
        return Vec3(e[0] * t, e[1] * t, e[2] * t);
    }

    Vec3 operator-(const Vec3 &v) const {
        return Vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
    }
    
    Vec3 operator/(double t) const {
        return Vec3(e[0] / t, e[1] / t, e[2] / t);
    }

    double length() const {
        return std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }

};

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

inline double dot(const Vec3 &u, const Vec3 &v) {
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

using Point3 = Vec3;  
using Color = Vec3;  

#endif