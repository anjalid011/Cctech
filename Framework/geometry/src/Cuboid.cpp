#include "Geometry.h"
#include "Triangle.h"
#include "Plotter.h"
#include "Transformations.h"
#include "StlToDat.h"
#include <iostream>
#include <fstream>
#include <vector>

Cuboid::Cuboid(double x, double y, double z, double width, double height, double depth)
    : x(x), y(y), z(z), width(width), height(height), depth(depth) {}

Cuboid::Cuboid() {
    x = 0;
    y = 0;
    z = 0;
    width = 10;
    height = 10;
    depth = 10;
}

void Cuboid::draw() {
    std::ofstream stlFile(".././geometry/scripts/cuboid.stl");
    if (!stlFile) {
        std::cerr << "Error: Unable to open STL file for Cuboid!\n";
        return;
    }

    stlFile << "solid Cuboid\n";

    // Define the 8 vertices of the cuboid
    Vec3 A(x, y, z);
    Vec3 B(x + width, y, z);
    Vec3 C(x + width, y + height, z);
    Vec3 D(x, y + height, z);
    Vec3 E(x, y, z + depth);
    Vec3 F(x + width, y, z + depth);
    Vec3 G(x + width, y + height, z + depth);
    Vec3 H(x, y + height, z + depth);

    std::vector<Triangle> triangles;

    // Front face
    triangles.emplace_back(A, B, C);
    triangles.emplace_back(A, C, D);

    // Back face
    triangles.emplace_back(E, F, G);
    triangles.emplace_back(E, G, H);

    // Left face
    triangles.emplace_back(A, D, H);
    triangles.emplace_back(A, H, E);

    // Right face
    triangles.emplace_back(B, C, G);
    triangles.emplace_back(B, G, F);

    // Top face
    triangles.emplace_back(D, C, G);
    triangles.emplace_back(D, G, H);

    // Bottom face
    triangles.emplace_back(A, B, F);
    triangles.emplace_back(A, F, E);

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

    stlFile << "endsolid Cuboid\n";
    stlFile.close();

    std::cout << "Cuboid STL file created successfully!\n";
}