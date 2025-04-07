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

Cylinder::Cylinder(double r, double h) : radius(r), height(h) {}

Cylinder::Cylinder() {
    radius = 10;
    height = 10;
}

void Cylinder::draw() {
    std::string objFilePath = ".././geometry/scripts/cylinder.obj";

    std::vector<Vec3> uniqueVertices;
    std::unordered_map<Vec3, int> vertexIndexMap;
    std::vector<Triangle> triangles;

    int numTheta = 50; // Number of angular divisions
    int numHeight = 10; // Number of height divisions

    auto getVertexIndex = [&](const Vec3& v) -> int {
        if (vertexIndexMap.find(v) == vertexIndexMap.end()) {
            vertexIndexMap[v] = uniqueVertices.size();
            uniqueVertices.push_back(v);
        }
        return vertexIndexMap[v];
    };

    // Start measuring time
    auto startTime = std::chrono::high_resolution_clock::now();

    // Generate the lateral surface of the cylinder
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        for (int j = 0; j < numHeight; j++) {
            double h1 = j * (height / numHeight);
            double h2 = (j + 1) * (height / numHeight);

            Vec3 v1(radius * cos(theta1), radius * sin(theta1), h1);
            Vec3 v2(radius * cos(theta2), radius * sin(theta2), h1);
            Vec3 v3(radius * cos(theta2), radius * sin(theta2), h2);
            Vec3 v4(radius * cos(theta1), radius * sin(theta1), h2);

            int i1 = getVertexIndex(v1);
            int i2 = getVertexIndex(v2);
            int i3 = getVertexIndex(v3);
            int i4 = getVertexIndex(v4);

            triangles.emplace_back(i1, i2, i3, uniqueVertices);
            triangles.emplace_back(i1, i3, i4, uniqueVertices);
        }
    }

    // Generate the top and bottom faces
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        Vec3 bottomCenter(0, 0, 0);
        Vec3 topCenter(0, 0, height);

        int bottomCenterIndex = getVertexIndex(bottomCenter);
        int topCenterIndex = getVertexIndex(topCenter);

        Vec3 v1(radius * cos(theta1), radius * sin(theta1), 0);
        Vec3 v2(radius * cos(theta2), radius * sin(theta2), 0);
        Vec3 v3(radius * cos(theta1), radius * sin(theta1), height);
        Vec3 v4(radius * cos(theta2), radius * sin(theta2), height);

        int i1 = getVertexIndex(v1);
        int i2 = getVertexIndex(v2);
        int i3 = getVertexIndex(v3);
        int i4 = getVertexIndex(v4);

        // Bottom face
        triangles.emplace_back(bottomCenterIndex, i1, i2, uniqueVertices);

        // Top face
        triangles.emplace_back(topCenterIndex, i3, i4, uniqueVertices);
    }

    // Stop measuring time
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Calculate memory usage
    size_t memoryForPoints = sizeof(Vec3) * uniqueVertices.size();
    size_t memoryForTriangles = sizeof(Triangle) * triangles.size();

    // Print statistics
    std::cout << "Cylinder Statistics:\n";
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

    fileHandler.convertOBJtoSTL(objFilePath, ".././geometry/scripts/cylinder.stl");
    fileHandler.convertSTLtoDAT(".././geometry/scripts/cylinder.stl", ".././geometry/scripts/cylinder.dat");

    std::cout << "Cylinder OBJ file created successfully at " << objFilePath << "!\n";

    // Optional: Perform transformations and plotting
    Transformations t;
    t.performTransformation(".././geometry/scripts/cylinder.dat", ".././geometry/scripts/transformedCylinder.dat", "Cylinder");

    Plotter::plot3D(".././geometry/scripts/cylinder.dat", "Cylinder");
}