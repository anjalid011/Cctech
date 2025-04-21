#include "Shapes/Geometry.h"
#include "Conversions/FileHandler.h"
#include "Shapes/Plotter.h"
#include "Shapes/Transformations.h"
#include "Conversions/Triangle.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <chrono>

#define PI 3.141592653589793


Sphere::Sphere(double r, double cx, double cy, double cz) : radius(r), centerX(cx), centerY(cy), centerZ(cz) {}


void Sphere::draw() {
    std::string objFilePath = "../geometry/scripts/sphere.obj";

    std::vector<Vec3> vertices;
    std::vector<Triangle> triangles;

    int stacks = 20;
    int slices = 20;

    for (int i = 0; i <= stacks; ++i) {
        float phi = M_PI * i / stacks;
        for (int j = 0; j <= slices; ++j) {
            float theta = 2 * M_PI * j / slices;
            float x = radius * sin(phi) * cos(theta) + centerX;
            float y = radius * sin(phi) * sin(theta) + centerY;
            float z = radius * cos(phi) + centerZ;
            vertices.emplace_back(x, y, z);
        }
    }

    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < slices; ++j) {
            int first = i * (slices + 1) + j;
            int second = first + slices + 1;
            triangles.emplace_back(first, second, first + 1, vertices);
            triangles.emplace_back(second, second + 1, first + 1, vertices);
        }
    }

    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, vertices, triangles)) {
        std::cerr << "Error: Failed to write OBJ file for sphere!\n";
        return;
    }

    std::cout << "Sphere OBJ file created successfully at " << objFilePath << "!\n";
}
