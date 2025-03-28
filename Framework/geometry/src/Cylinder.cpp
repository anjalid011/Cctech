#include "Geometry.h"
#include "Plotter.h"
#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.141592653589793

Cylinder::Cylinder(double r, double h) : radius(r), height(h) {}

void Cylinder::draw() const {
    std::ofstream file(".././geometry/scripts/cylinder.txt");
    if (!file) {
        std::cerr << "Error: Unable to open cylinder file!\n";
        return;
    }

    int numTheta = 100; // Number of rotations
    int numT = 50;      // Points along the vertical line

    for (int i = 0; i <= numTheta; i++) {
        double theta = i * (2 * PI / numTheta);

        for (int j = 0; j <= numT; j++) {
            double t = j * (1.0 / numT);
            
            // Compute rotated coordinates
            double x = radius * cos(theta);
            double y = radius * sin(theta);
            double z = height * t;

            file << x << " " << y << " " << z << "\n";
        }
        file << "\n"; // Separate each curve
    }

    file.close();
    std::cout << "Cylinder drawn successfully!\n";
}

void Cylinder::savePoints(const std::string& outputFile) {
    std::ofstream file(outputFile);
    if (!file) {
        std::cerr << "Error: Unable to create file " << outputFile << "\n";
        return;
    }

    for (const auto& point : points) {
        file << point[0] << " " << point[1] << " " << point[2] << "\n";
    }
    file.close();
}