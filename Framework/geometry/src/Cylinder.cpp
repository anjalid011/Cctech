#include "Geometry.h"
#include "Plotter.h"
#include "Transformations.h"
#include "StlToDat.h"
#include "Triangle.h"
#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.141592653589793

Cylinder::Cylinder(double r, double h) : radius(r), height(h) {}

Cylinder::Cylinder() {
    radius = 10;
    height = 10;
}

void Cylinder::draw() {
    std::ofstream stlFile(".././geometry/scripts/cylinder.stl");
    if (!stlFile) {
        std::cerr << "Error: Unable to open STL file for Cylinder!\n";
        return;
    }

    stlFile << "solid Cylinder\n";

    int numTheta = 100; // Number of angular divisions
    int numT = 50;      // Number of height divisions

    std::vector<Triangle> triangles;

    // Generate the lateral surface of the cylinder
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        for (int j = 0; j < numT; j++) {
            double t1 = j * (1.0 / numT);
            double t2 = (j + 1) * (1.0 / numT);

            // Compute the four vertices of the current quad
            Vec3 v1(radius * cos(theta1), radius * sin(theta1), height * t1);
            Vec3 v2(radius * cos(theta2), radius * sin(theta2), height * t1);
            Vec3 v3(radius * cos(theta2), radius * sin(theta2), height * t2);
            Vec3 v4(radius * cos(theta1), radius * sin(theta1), height * t2);

            // Create two triangles for the quad
            triangles.emplace_back(v1, v2, v3);
            triangles.emplace_back(v1, v3, v4);
        }
    }

    // Generate the top and bottom faces of the cylinder
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        // Bottom face
        Vec3 v1(radius * cos(theta1), radius * sin(theta1), 0);
        Vec3 v2(radius * cos(theta2), radius * sin(theta2), 0);
        Vec3 v3(0, 0, 0);
        triangles.emplace_back(v1, v2, v3);

        // Top face
        Vec3 v4(radius * cos(theta1), radius * sin(theta1), height);
        Vec3 v5(radius * cos(theta2), radius * sin(theta2), height);
        Vec3 v6(0, 0, height);
        triangles.emplace_back(v4, v5, v6);
    }

    // Write triangles to STL file
    for (const auto& t : triangles) {
        stlFile << "  facet normal " << t.normal.x << " " << t.normal.y << " " << t.normal.z << "\n";
        stlFile << "    outer loop\n";
        stlFile << "      vertex " << t.v1.x << " " << t.v1.y << " " << t.v1.z << "\n";
        stlFile << "      vertex " << t.v2.x << " " << t.v2.y << " " << t.v2.z << "\n";
        stlFile << "      vertex " << t.v3.x << " " << t.v3.y << " " << t.v3.z << "\n";
        stlFile << "    endloop\n";
        stlFile << "  endfacet\n";
    }

    stlFile << "endsolid Cylinder\n";
    stlFile.close();

    std::cout << "Cylinder STL file created successfully!\n";
}