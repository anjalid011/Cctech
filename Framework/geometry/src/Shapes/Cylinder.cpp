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

// Add this to your Cylinder class
Cylinder::Cylinder(double r, double h, double cx, double cy, double cz)
    : radius(r), height(h), centerX(cx), centerY(cy), centerZ(cz) {}

// Modify draw()
void Cylinder::draw() {
    std::string objFilePath = "../geometry/scripts/cylinder.obj";

    std::vector<Vec3> vertices;
    std::vector<Triangle> triangles;

    int slices = 20;

    vertices.emplace_back(centerX, centerY + height / 2, centerZ); // Top center
    vertices.emplace_back(centerX, centerY - height / 2, centerZ); // Bottom center

    for (int i = 0; i <= slices; ++i) {
        float theta = 2 * M_PI * i / slices;
        float x = radius * cos(theta);
        float z = radius * sin(theta);

        vertices.emplace_back(centerX + x, centerY + height / 2, centerZ + z);  // Top circle
        vertices.emplace_back(centerX + x, centerY - height / 2, centerZ + z);  // Bottom circle
    }

    for (int i = 2; i < vertices.size() - 2; i += 2) {
        triangles.emplace_back(0, i, i + 2, vertices);       // Top face
        triangles.emplace_back(1, i + 1, i + 3, vertices);   // Bottom face
    }

    for (int i = 2; i < vertices.size() - 2; i += 2) {
        triangles.emplace_back(i, i + 2, i + 3, vertices);
        triangles.emplace_back(i, i + 3, i + 1, vertices);
    }

    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, vertices, triangles)) {
        std::cerr << "Error: Failed to write OBJ file for cylinder!\n";
        return;
    }

    std::cout << "Cylinder OBJ file created successfully at " << objFilePath << "!\n";
}
