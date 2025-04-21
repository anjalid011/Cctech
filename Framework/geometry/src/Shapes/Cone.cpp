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

// Add this to your Cone class
Cone::Cone(double r, double h, double cx, double cy, double cz)
    : radius(r), height(h), centerX(cx), centerY(cy), centerZ(cz) {}

// Modify draw()
void Cone::draw() {
    std::string objFilePath = "../geometry/scripts/cone.obj";

    std::vector<Vec3> vertices;
    std::vector<Triangle> triangles;

    int slices = 20;

    vertices.emplace_back(centerX, centerY + height, centerZ);  // Apex

    for (int i = 0; i <= slices; ++i) {
        float theta = 2 * M_PI * i / slices;
        float x = centerX + radius * cos(theta);
        float z = centerZ + radius * sin(theta);
        float y = centerY;
        vertices.emplace_back(x, y, z);
    }

    for (int i = 1; i <= slices; ++i) {
        triangles.emplace_back(0, i, i + 1, vertices);
    }

    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, vertices, triangles)) {
        std::cerr << "Error: Failed to write OBJ file for cone!\n";
        return;
    }

    std::cout << "Cone OBJ file created successfully at " << objFilePath << "!\n";
}
