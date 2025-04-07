#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>

class Vec3 {
    public :
        double x,y,z;

        Vec3(): x(0), y(0), z(0) {}
        Vec3(double x, double y, double z): x(x), y(y), z(z) {}

        Vec3 operator-(const Vec3& v) const {
            return Vec3(x - v.x, y-v.y, z-v.z);
        }

        Vec3 cross(const Vec3& v) const {
            return Vec3(
                y*v.z -z*v.y,
                z*v.x - x*v.z,
                x*v.y - y*v.x
            );
        }

        void normalize() {
            double length = sqrt(x*x +y*y + z*z);
            if (length>0) {
                x /= length;
                y /= length;
                z /= length;
            }
        }
};

// #define Vec3 vector<double>

class Triangle {
    public:
    Vec3 v1, v2, v3;
    Vec3 normal;

    Triangle(){}
    Triangle(Vec3 a, Vec3 b,Vec3 c): v1(a), v2(b), v3(c) {
        computeNormal();
    }

    void computeNormal() {
        Vec3 edge1 = v2 -v1;
        Vec3 edge2 = v3 -v1;
        normal = edge1.cross(edge2);
        normal.normalize();
    }

    int getpointCount() const { return 3;}
};

#endif //TRIANGLE_H

