#include "Shapes/Geometry.h"
#include "Conversions/FileHandler.h"
#include "Shapes/Plotter.h"
#include "Shapes/Transformations.h"
#include "Conversions/Triangle.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#define PI 3.141592653589793

Cone::Cone(double r, double h) : radius(r), height(h) {}

Cone::Cone() {
    radius = 10;
    height = 10;
}

void Cone::draw() {
    std::string objFilePath = ".././geometry/scripts/cone.obj";

    std::vector<Triangle> triangles;

    int numTheta = 50; // Number of angular divisions

    // Generate the lateral surface of the cone
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        Vec3 apex(0, 0, height); // Apex of the cone
        Vec3 v1(radius * cos(theta1), radius * sin(theta1), 0);
        Vec3 v2(radius * cos(theta2), radius * sin(theta2), 0);

        triangles.emplace_back(apex, v1, v2);
    }

    // Generate the base of the cone
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        Vec3 center(0, 0, 0); // Center of the base
        Vec3 v1(radius * cos(theta1), radius * sin(theta1), 0);
        Vec3 v2(radius * cos(theta2), radius * sin(theta2), 0);

        triangles.emplace_back(center, v1, v2);
    }

    // Write to OBJ file
    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, triangles)) {
        std::cerr << "Error: Failed to write OBJ file!\n";
        return;
    }
    fileHandler.convertOBJtoSTL(objFilePath, ".././geometry/scripts/cone.stl");
    fileHandler.convertSTLtoDAT(".././geometry/scripts/cone.stl", ".././geometry/scripts/cone.dat");

    std::cout << "Cone OBJ file created successfully at " << objFilePath << "!\n";

    // Optional: Perform transformations and plotting
    Transformations t;
    t.performTransformation(".././geometry/scripts/cone.dat", ".././geometry/scripts/transformedCone.dat", "Cone");

    Plotter::plot3D(objFilePath, "Cone");
}