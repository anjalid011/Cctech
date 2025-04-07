#include "Shapes/Geometry.h"
#include "Shapes/Plotter.h"
#include "Shapes/Transformations.h"
#include "Conversions/FileHandler.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "Conversions/Triangle.h"

#define PI 3.141592653589793

Sphere::Sphere(double r) : radius(r) {}

Sphere::Sphere() {
    radius = 10;
}

void Sphere::draw() {
    std::string objFilePath = ".././geometry/scripts/sphere.obj";

    std::vector<Triangle> triangles;

    int numTheta = 500;  // Number of azimuthal divisions
    int numPhi = 500;    // Number of polar divisions

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

            // Create two triangles for the current quad
            triangles.emplace_back(v1, v2, v3);
            triangles.emplace_back(v1, v3, v4);
        }
    }

    // Write to OBJ file
    FileHandler fileHandler;
    if (!fileHandler.writeOBJFile(objFilePath, triangles)) {
        std::cerr << "Error: Failed to write OBJ file!\n";
        return;
    }\
    fileHandler.convertOBJtoSTL(objFilePath, ".././geometry/scripts/sphere.stl");
    fileHandler.convertSTLtoDAT(".././geometry/scripts/sphere.stl", ".././geometry/scripts/sphere.dat");

    std::cout << "Sphere OBJ file created successfully at " << objFilePath << "!\n";

    // Optional: Perform transformations and plotting
    Transformations t;
    t.performTransformation(".././geometry/scripts/sphere.dat", ".././geometry/scripts/transformedSphere.dat", "Sphere");

    Plotter::plot3D(objFilePath, "Sphere");
}