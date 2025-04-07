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

Sphere::Sphere(double r) : radius(r) {}

Sphere::Sphere() {
    radius = 10;
}

void Sphere::draw() {
    std::string objFilePath = ".././geometry/scripts/sphere.obj";

    std::vector<Vec3> uniqueVertices;
    std::unordered_map<Vec3, int> vertexIndexMap;
    std::vector<Triangle> triangles;

    int numTheta = 500; // Number of azimuthal divisions
    int numPhi = 500;   // Number of polar divisions

    auto getVertexIndex = [&](const Vec3& v) -> int {
        if (vertexIndexMap.find(v) == vertexIndexMap.end()) {
            vertexIndexMap[v] = uniqueVertices.size();
            uniqueVertices.push_back(v);
        }
        return vertexIndexMap[v];
    };

    // Start measuring time
    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        for (int j = 0; j < numPhi; j++) {
            double phi1 = j * (PI / numPhi);
            double phi2 = (j + 1) * (PI / numPhi);

            // Compute the four vertices of the current quad
            Vec3 v1(radius * cos(theta1) * sin(phi1), radius * sin(theta1) * sin(phi1), radius * cos(phi1));
            Vec3 v2(radius * cos(theta2) * sin(phi1), radius * sin(theta2) * sin(phi1), radius * cos(phi1));
            Vec3 v3(radius * cos(theta2) * sin(phi2), radius * sin(theta2) * sin(phi2), radius * cos(phi2));
            Vec3 v4(radius * cos(theta1) * sin(phi2), radius * sin(theta1) * sin(phi2), radius * cos(phi2));

            // Get indices for the vertices
            int i1 = getVertexIndex(v1);
            int i2 = getVertexIndex(v2);
            int i3 = getVertexIndex(v3);
            int i4 = getVertexIndex(v4);

            // Create two triangles for the quad
            triangles.emplace_back(i1, i2, i3, uniqueVertices);
            triangles.emplace_back(i1, i3, i4, uniqueVertices);
        }
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

    fileHandler.convertOBJtoSTL(objFilePath, ".././geometry/scripts/sphere.stl");
    fileHandler.convertSTLtoDAT(".././geometry/scripts/sphere.stl", ".././geometry/scripts/sphere.dat");

    std::cout << "Sphere OBJ file created successfully at " << objFilePath << "!\n";

    // Optional: Perform transformations and plotting
    Transformations t;
    t.performTransformation(".././geometry/scripts/sphere.dat", ".././geometry/scripts/transformedSphere.dat", "Sphere");

    Plotter::plot3D(".././geometry/scripts/sphere.dat", "Sphere");
}