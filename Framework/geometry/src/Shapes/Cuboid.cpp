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

    // Define the 8 vertices of the cuboid
    Vec3 A(-width / 2, -height / 2, -depth / 2);
    Vec3 B(width / 2, -height / 2, -depth / 2);
    Vec3 C(width / 2, height / 2, -depth / 2);
    Vec3 D(-width / 2, height / 2, -depth / 2);
    Vec3 E(-width / 2, -height / 2, depth / 2);
    Vec3 F(width / 2, -height / 2, depth / 2);
    Vec3 G(width / 2, height / 2, depth / 2);
    Vec3 H(-width / 2, height / 2, depth / 2);

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

    // Write to OBJ file
    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, uniqueVertices, triangles)) {
        std::cerr << "Error: Failed to write OBJ file!\n";
        return;
    }

    std::cout << "Cuboid OBJ file created successfully at " << objFilePath << "!\n";

    // Start measuring time
    // auto startTime1 = std::chrono::high_resolution_clock::now();

    // fileHandler.convertOBJtoSTL(objFilePath, ".././geometry/scripts/cuboid.stl");

    // auto endTime1 = std::chrono::high_resolution_clock::now();
    // auto durationforOBJtoSTL = std::chrono::duration_cast<std::chrono::milliseconds>(endTime1 - startTime1);
    // std::cout << "Time Taken For Obj to STL: " << durationforOBJtoSTL.count() << " ms\n";

    // auto startTime2 = std::chrono::high_resolution_clock::now();

    // fileHandler.convertSTLtoDAT(".././geometry/scripts/cuboid.stl", ".././geometry/scripts/cuboid.dat");

    // auto endTime2 = std::chrono::high_resolution_clock::now();
    // auto durationforSTLtoDAT = std::chrono::duration_cast<std::chrono::milliseconds>(endTime2 - startTime2);
    // std::cout << "Time Taken For STL to DAT: " << durationforSTLtoDAT.count() << " ms\n";

    // std::cout << "Cuboid OBJ file created successfully at " << objFilePath << "!\n";

    // Optional: Perform transformations and plotting
    // Transformations t;
    // t.performTransformation(".././geometry/scripts/cuboid.dat", ".././geometry/scripts/transformedCuboid.dat", "Cuboid");

    // Plotter::plot3D(".././geometry/scripts/cuboid.dat", "Cuboid");
}