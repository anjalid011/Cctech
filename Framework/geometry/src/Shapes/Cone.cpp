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

Cone::Cone(double r, double h) : radius(r), height(h) {}

Cone::Cone() {
    radius = 10;
    height = 10;
}

void Cone::draw() {
    std::string objFilePath = "../geometry/scripts/cone.obj";

    std::vector<Vec3> vertices;
    std::vector<Triangle> triangles;

    int slices = 20; // Number of vertical slices

    // Add the apex of the cone
    vertices.emplace_back(0.0f, height, 0.0f);

    // Add the base vertices
    for (int i = 0; i <= slices; ++i) {
        float theta = 2 * M_PI * i / slices;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        vertices.emplace_back(x, 0.0f, z);
    }

    // Generate triangles for the cone
    for (int i = 1; i <= slices; ++i) {
        triangles.emplace_back(0, i, i + 1, vertices); // Apex to base
    }

    // Write to OBJ file
    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, vertices, triangles)) {
        std::cerr << "Error: Failed to write OBJ file for cone!\n";
        return;
    }

    std::cout << "Cone OBJ file created successfully at " << objFilePath << "!\n";
}