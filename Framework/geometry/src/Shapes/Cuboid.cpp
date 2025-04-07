#include "Shapes/Geometry.h"
#include "Conversions/FileHandler.h"
#include "Shapes/Plotter.h"
#include "Shapes/Transformations.h"
#include "Conversions/Triangle.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <chrono>

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

    std::vector<Vec3> uniqueVertices;
    std::unordered_map<Vec3, int> vertexIndexMap;
    std::vector<Triangle> triangles;

    auto getVertexIndex = [&](const Vec3& v) -> int {
        if (vertexIndexMap.find(v) == vertexIndexMap.end()) {
            vertexIndexMap[v] = uniqueVertices.size();
            uniqueVertices.push_back(v);
        }
        return vertexIndexMap[v];
    };

    // Start measuring time
    auto startTime = std::chrono::high_resolution_clock::now();

    // Define the 8 vertices of the cuboid
    Vec3 A(x, y, z);
    Vec3 B(x + width, y, z);
    Vec3 C(x + width, y + height, z);
    Vec3 D(x, y + height, z);
    Vec3 E(x, y, z + depth);
    Vec3 F(x + width, y, z + depth);
    Vec3 G(x + width, y + height, z + depth);
    Vec3 H(x, y + height, z + depth);

    // Get indices for the vertices
    int iA = getVertexIndex(A);
    int iB = getVertexIndex(B);
    int iC = getVertexIndex(C);
    int iD = getVertexIndex(D);
    int iE = getVertexIndex(E);
    int iF = getVertexIndex(F);
    int iG = getVertexIndex(G);
    int iH = getVertexIndex(H);

    // Front face
    triangles.emplace_back(iA, iB, iC, uniqueVertices);
    triangles.emplace_back(iA, iC, iD, uniqueVertices);

    // Back face
    triangles.emplace_back(iE, iF, iG, uniqueVertices);
    triangles.emplace_back(iE, iG, iH, uniqueVertices);

    // Left face
    triangles.emplace_back(iA, iD, iH, uniqueVertices);
    triangles.emplace_back(iA, iH, iE, uniqueVertices);

    // Right face
    triangles.emplace_back(iB, iC, iG, uniqueVertices);
    triangles.emplace_back(iB, iG, iF, uniqueVertices);

    // Top face
    triangles.emplace_back(iD, iC, iG, uniqueVertices);
    triangles.emplace_back(iD, iG, iH, uniqueVertices);

    // Bottom face
    triangles.emplace_back(iA, iB, iF, uniqueVertices);
    triangles.emplace_back(iA, iF, iE, uniqueVertices);

     // Stop measuring time
     auto endTime = std::chrono::high_resolution_clock::now();
     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Calculate memory usage
    size_t memoryForPoints = sizeof(Vec3) * uniqueVertices.size();
    size_t memoryForTriangles = sizeof(Triangle) * triangles.size();

    // Print statistics
    std::cout << "Cuboid Statistics:\n";
    std::cout << "Number of Points: " << uniqueVertices.size() << "\n";
    std::cout << "Number of Triangles: " << triangles.size() << "\n";
    std::cout << "Memory for Points: " << memoryForPoints << " bytes\n";
    std::cout << "Memory for Triangles: " << memoryForTriangles << " bytes\n";
    std::cout << "Time Taken: " << duration.count() << " ms\n";

    // Write to OBJ file
    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, uniqueVertices, triangles)) {
        std::cerr << "Error: Failed to write OBJ file!\n";
        return;
    }

    fileHandler.convertOBJtoSTL(objFilePath, ".././geometry/scripts/cuboid.stl");
    fileHandler.convertSTLtoDAT(".././geometry/scripts/cuboid.stl", ".././geometry/scripts/cuboid.dat");

    std::cout << "Cuboid OBJ file created successfully at " << objFilePath << "!\n";

    // Optional: Perform transformations and plotting
    Transformations t;
    t.performTransformation(".././geometry/scripts/cuboid.dat", ".././geometry/scripts/transformedCuboid.dat", "Cuboid");

    Plotter::plot3D(".././geometry/scripts/cuboid.dat", "Cuboid");
}