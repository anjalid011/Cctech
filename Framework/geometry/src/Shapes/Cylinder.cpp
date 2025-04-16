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

Cylinder::Cylinder(double r, double h) : radius(r), height(h) {}

Cylinder::Cylinder() {
    radius = 10;
    height = 10;
}

void Cylinder::draw() {
    std::string objFilePath = "../geometry/scripts/cylinder.obj";

    std::vector<Vec3> vertices;
    std::vector<Triangle> triangles;

    int slices = 20; // Number of vertical slices

    // Add the top and bottom center points
    vertices.emplace_back(0.0f, height / 2, 0.0f); // Top center
    vertices.emplace_back(0.0f, -height / 2, 0.0f); // Bottom center

    // Add the top and bottom circle vertices
    for (int i = 0; i <= slices; ++i) {
        float theta = 2 * M_PI * i / slices;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        vertices.emplace_back(x, height / 2, z);  // Top circle
        vertices.emplace_back(x, -height / 2, z); // Bottom circle
    }

    // Generate triangles for the top and bottom faces
    for (int i = 2; i < vertices.size() - 2; i += 2) {
        triangles.emplace_back(0, i, i + 2, vertices); // Top face
        triangles.emplace_back(1, i + 1, i + 3, vertices); // Bottom face
    }

    // Generate triangles for the side faces
    for (int i = 2; i < vertices.size() - 2; i += 2) {
        triangles.emplace_back(i, i + 2, i + 3, vertices);
        triangles.emplace_back(i, i + 3, i + 1, vertices);
    }

    // Write to OBJ file
    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, vertices, triangles)) {
        std::cerr << "Error: Failed to write OBJ file for cylinder!\n";
        return;
    }

    std::cout << "Cylinder OBJ file created successfully at " << objFilePath << "!\n";
}