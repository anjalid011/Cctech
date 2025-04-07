#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>
#include <vector>
#include <unordered_map>
#include <tuple>

class Vec3 {
public:
    double x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    bool operator==(const Vec3& v) const {
        return std::abs(x - v.x) < 1e-6 && std::abs(y - v.y) < 1e-6 && std::abs(z - v.z) < 1e-6;
    }

    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    Vec3 cross(const Vec3& v) const {
        return Vec3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    void normalize() {
        double length = sqrt(x * x + y * y + z * z);
        if (length > 0) {
            x /= length;
            y /= length;
            z /= length;
        }
    }
};

// Hash function for Vec3 to use in unordered_map
namespace std {
    template <>
    struct hash<Vec3> {
        size_t operator()(const Vec3& v) const {
            return hash<double>()(v.x) ^ hash<double>()(v.y) ^ hash<double>()(v.z);
        }
    };
}

class Triangle {
public:
    int v1, v2, v3; // Indices of vertices in the unique vertex list
    Vec3 normal;

    Triangle() {}
    Triangle(int a, int b, int c, const std::vector<Vec3>& vertices) : v1(a), v2(b), v3(c) {
        computeNormal(vertices);
    }

    Triangle(const Vec3& a, const Vec3& b, const Vec3& c) {
        // Used when you don't use index-based vertex lists
        std::vector<Vec3> temp = { a, b, c };
        v1 = 0;
        v2 = 1;
        v3 = 2;
        computeNormal(temp);
    }

    void computeNormal(const std::vector<Vec3>& vertices) {
        Vec3 edge1 = vertices[v2] - vertices[v1];
        Vec3 edge2 = vertices[v3] - vertices[v1];
        normal = edge1.cross(edge2);
        normal.normalize();
    }
};

#endif // TRIANGLE_H