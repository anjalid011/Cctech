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

Cylinder::Cylinder(double r, double h) : radius(r), height(h) {}

Cylinder::Cylinder() {
    radius = 10;
    height = 10;
}

void Cylinder::draw() {
    std::string objFilePath = ".././geometry/scripts/cylinder.obj";

    std::vector<Triangle> triangles;

    int numTheta = 50; // Number of angular divisions
    int numHeight = 10; // Number of height divisions

    // Generate the lateral surface of the cylinder
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        for (int j = 0; j < numHeight; j++) {
            double h1 = j * (height / numHeight);
            double h2 = (j + 1) * (height / numHeight);

            // Compute the four vertices of the current quad
            Vec3 v1(radius * cos(theta1), radius * sin(theta1), h1);
            Vec3 v2(radius * cos(theta2), radius * sin(theta2), h1);
            Vec3 v3(radius * cos(theta2), radius * sin(theta2), h2);
            Vec3 v4(radius * cos(theta1), radius * sin(theta1), h2);

            // Create two triangles for the quad
            triangles.emplace_back(v1, v2, v3);
            triangles.emplace_back(v1, v3, v4);
        }
    }

    // Generate the top and bottom faces
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        // Bottom face
        Vec3 v1(0, 0, 0);
        Vec3 v2(radius * cos(theta1), radius * sin(theta1), 0);
        Vec3 v3(radius * cos(theta2), radius * sin(theta2), 0);
        triangles.emplace_back(v1, v2, v3);

        // Top face
        Vec3 v4(0, 0, height);
        Vec3 v5(radius * cos(theta1), radius * sin(theta1), height);
        Vec3 v6(radius * cos(theta2), radius * sin(theta2), height);
        triangles.emplace_back(v4, v5, v6);
    }

    // Write to OBJ file
    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, triangles)) {
        std::cerr << "Error: Failed to write OBJ file!\n";
        return;
    }
    fileHandler.convertOBJtoSTL(objFilePath, ".././geometry/scripts/cylinder.stl");
    fileHandler.convertSTLtoDAT(".././geometry/scripts/cylinder.stl", ".././geometry/scripts/cylinder.dat");
    std::cout << "Cylinder OBJ file created successfully at " << objFilePath << "!\n";

    // Optional: Perform transformations and plotting
    Transformations t;
    t.performTransformation(".././geometry/scripts/cylinder.dat", ".././geometry/scripts/transformedCylinder.dat", "Cylinder");

    Plotter::plot3D(objFilePath, "Cylinder");
}