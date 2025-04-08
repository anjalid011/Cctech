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
    std::string objFilePath = ".././geometry/scripts/cone.obj";

    std::vector<Vec3> uniqueVertices;
    std::unordered_map<Vec3, int> vertexIndexMap;
    std::vector<Triangle> triangles;

    int numTheta = 50; // Number of angular divisions

    auto getVertexIndex = [&](const Vec3& v) -> int {
        if (vertexIndexMap.find(v) == vertexIndexMap.end()) {
            vertexIndexMap[v] = uniqueVertices.size();
            uniqueVertices.push_back(v);
        }
        return vertexIndexMap[v];
    };

    // Generate the lateral surface of the cone
    Vec3 apex(0, 0, height); // Apex of the cone
    int apexIndex = getVertexIndex(apex);

    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        Vec3 v1(radius * cos(theta1), radius * sin(theta1), 0);
        Vec3 v2(radius * cos(theta2), radius * sin(theta2), 0);

        int i1 = getVertexIndex(v1);
        int i2 = getVertexIndex(v2);

        triangles.emplace_back(apexIndex, i1, i2, uniqueVertices);
    }

    // Generate the base of the cone
    Vec3 center(0, 0, 0); // Center of the base
    int centerIndex = getVertexIndex(center);

    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        Vec3 v1(radius * cos(theta1), radius * sin(theta1), 0);
        Vec3 v2(radius * cos(theta2), radius * sin(theta2), 0);

        int i1 = getVertexIndex(v1);
        int i2 = getVertexIndex(v2);

        triangles.emplace_back(centerIndex, i1, i2, uniqueVertices);
    }
   
    // Calculate memory usage
    size_t memoryForPoints = sizeof(Vec3) * uniqueVertices.size();
    size_t memoryForTriangles = sizeof(Triangle) * triangles.size();

    // Print statistics
    std::cout << "Cylinder Statistics:\n";
    std::cout << "Number of Points: " << uniqueVertices.size() << "\n";
    std::cout << "Number of Triangles: " << triangles.size() << "\n";
    std::cout << "Memory for Points: " << memoryForPoints << " bytes\n";
    std::cout << "Memory for Triangles: " << memoryForTriangles << " bytes\n";

    // Write to OBJ file
    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, uniqueVertices, triangles)) {
        std::cerr << "Error: Failed to write OBJ file!\n";
        return;
    }

    // Start measuring time
    auto startTime1 = std::chrono::high_resolution_clock::now();

    fileHandler.convertOBJtoSTL(objFilePath, ".././geometry/scripts/cone.stl");

    auto endTime1 = std::chrono::high_resolution_clock::now();
    auto durationforOBJtoSTL = std::chrono::duration_cast<std::chrono::milliseconds>(endTime1 - startTime1);
    std::cout << "Time Taken For Obj to STL: " << durationforOBJtoSTL.count() << " ms\n";

    auto startTime2 = std::chrono::high_resolution_clock::now();

    fileHandler.convertSTLtoDAT(".././geometry/scripts/cone.stl", ".././geometry/scripts/cone.dat");

    auto endTime2 = std::chrono::high_resolution_clock::now();
    auto durationforSTLtoDAT = std::chrono::duration_cast<std::chrono::milliseconds>(endTime2 - startTime2);
    std::cout << "Time Taken For STL to DAT: " << durationforSTLtoDAT.count() << " ms\n";

    std::cout << "Cone OBJ file created successfully at " << objFilePath << "!\n";

    // Optional: Perform transformations and plotting
    Transformations t;
    t.performTransformation(".././geometry/scripts/cone.dat", ".././geometry/scripts/transformedCone.dat", "Cone");

    Plotter::plot3D(".././geometry/scripts/cone.dat", "Cone");
}