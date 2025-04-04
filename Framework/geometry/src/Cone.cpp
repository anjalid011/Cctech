#include "Geometry.h"
#include "Triangle.h"
#include "Plotter.h"
#include "Transformations.h"
#include "StlToDat.h"
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
    std::ofstream stlFile("../geometry/scripts/cone.stl");
    if (!stlFile) {
        std::cerr << "Error: Unable to open STL file for Cone!\n";
        return;
    }

    stlFile << "solid Cone\n";

    int numTheta = 100; // Number of angular divisions
    std::vector<Triangle> triangles;

    // Generate the lateral surface of the cone
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        Vec3 v1(0, 0, height); // Apex of the cone
        Vec3 v2(radius * cos(theta1), radius * sin(theta1), 0);
        Vec3 v3(radius * cos(theta2), radius * sin(theta2), 0);

        triangles.emplace_back(v1, v2, v3);
    }

    // Generate the base of the cone
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        Vec3 v1(0, 0, 0); // Center of the base
        Vec3 v2(radius * cos(theta1), radius * sin(theta1), 0);
        Vec3 v3(radius * cos(theta2), radius * sin(theta2), 0);

        triangles.emplace_back(v1, v2, v3);
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

    stlFile << "endsolid Cone\n";
    stlFile.close();

    std::cout << "Cone STL file created successfully!\n";
}