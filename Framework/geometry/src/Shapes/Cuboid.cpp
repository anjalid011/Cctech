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
    std::string objFilePath = "../geometry/scripts/cuboid.obj";

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

    // Define 8 vertices relative to (x, y, z) as center
    Vec3 A(x - width / 2, y - height / 2, z - depth / 2);
    Vec3 B(x + width / 2, y - height / 2, z - depth / 2);
    Vec3 C(x + width / 2, y + height / 2, z - depth / 2);
    Vec3 D(x - width / 2, y + height / 2, z - depth / 2);
    Vec3 E(x - width / 2, y - height / 2, z + depth / 2);
    Vec3 F(x + width / 2, y - height / 2, z + depth / 2);
    Vec3 G(x + width / 2, y + height / 2, z + depth / 2);
    Vec3 H(x - width / 2, y + height / 2, z + depth / 2);

    // Indexing for triangles
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

    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, uniqueVertices, triangles)) {
        std::cerr << "Error: Failed to write OBJ file!\n";
        return;
    }

    std::cout << "Cuboid OBJ file created successfully at " << objFilePath << "!\n";
}
