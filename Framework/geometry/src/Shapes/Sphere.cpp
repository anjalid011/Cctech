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

Sphere::Sphere(double r) : radius(r) {}

Sphere::Sphere() {
    radius = 10;
}

void Sphere::draw() {
    std::string objFilePath = "../geometry/scripts/sphere.obj";

    std::vector<Vec3> vertices;
    std::vector<Triangle> triangles;

    int stacks = 20; // Number of horizontal slices
    int slices = 20; // Number of vertical slices

    // Generate vertices
    for (int i = 0; i <= stacks; ++i) {
        float phi = M_PI * i / stacks; // Latitude angle
        for (int j = 0; j <= slices; ++j) {
            float theta = 2 * M_PI * j / slices; // Longitude angle
            float x = radius * sin(phi) * cos(theta);
            float y = radius * sin(phi) * sin(theta);
            float z = radius * cos(phi);
            vertices.emplace_back(x, y, z);
        }
    }

    // Generate triangles
    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < slices; ++j) {
            int first = i * (slices + 1) + j;
            int second = first + slices + 1;

            triangles.emplace_back(first, second, first + 1, vertices);
            triangles.emplace_back(second, second + 1, first + 1, vertices);
        }
    }

    // Write to OBJ file
    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, vertices, triangles)) {
        std::cerr << "Error: Failed to write OBJ file for sphere!\n";
        return;
    }

    std::cout << "Sphere OBJ file created successfully at " << objFilePath << "!\n";
}
