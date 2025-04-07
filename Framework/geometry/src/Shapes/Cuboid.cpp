#include "Shapes/Geometry.h"
#include "Conversions/FileHandler.h"
#include "Shapes/Plotter.h"
#include "Shapes/Transformations.h"
#include "Conversions/Triangle.h"
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
    std::string objFilePath = ".././geometry/scripts/cuboid.obj";

    std::vector<Triangle> triangles;

    // Define the 8 vertices of the cuboid
    Vec3 A(x, y, z);
    Vec3 B(x + width, y, z);
    Vec3 C(x + width, y + height, z);
    Vec3 D(x, y + height, z);
    Vec3 E(x, y, z + depth);
    Vec3 F(x + width, y, z + depth);
    Vec3 G(x + width, y + height, z + depth);
    Vec3 H(x, y + height, z + depth);

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

    // Write to OBJ file
    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, triangles)) {
        std::cerr << "Error: Failed to write OBJ file!\n";
        return;
    }
    fileHandler.convertOBJtoSTL(objFilePath, ".././geometry/scripts/cuboid.stl");
    fileHandler.convertSTLtoDAT(".././geometry/scripts/cuboid.stl", ".././geometry/scripts/cuboid.dat");

    std::cout << "Cuboid OBJ file created successfully at " << objFilePath << "!\n";

    // Optional: Perform transformations and plotting
    Transformations t;
    t.performTransformation(".././geometry/scripts/cuboid.dat", ".././geometry/scripts/transformedCuboid.dat", "Cuboid");

    Plotter::plot3D(objFilePath, "Cuboid");
}