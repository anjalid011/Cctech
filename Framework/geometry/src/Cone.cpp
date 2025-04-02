#include "Geometry.h"
#include "Plotter.h"
#include "Transformations.h"
#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.141592653589793

Cone::Cone(double r, double h) : radius(r), height(h) {}

Cone::Cone(){
    radius=10;
    height=10;
}

void Cone::draw() {
    double radius, height;
    std::cout << "Enter base radius and height for Cone: ";
    std::cin >> radius >> height;
    Cone cone(radius, height);
    std::ofstream file("../geometry/scripts/shape.txt");
    if (!file) {
        std::cerr << "Error: Unable to open cone file!\n";
        return;
    }

    int numTheta = 100; // Number of rotations
    int numT = 50;      // Points along the slanted line

    for (int i = 0; i <= numTheta; i++) {
        double theta = i * (2 * PI / numTheta);

        for (int j = 0; j <= numT; j++) {
            double t = j * (1.0 / numT);
            
            // Compute rotated coordinates
            double x = radius * t * cos(theta);
            double y = radius * t * sin(theta);
            double z = height * (1 - t);

            file << x << " " << y << " " << z << "\n";
        }
        file << "\n"; // Separate each curve
    }
    file.close();
    Plotter::plot3D(".././geometry/scripts/shape.txt","Cone");
    //Plotter::plot3DTrans(".././geometry/scripts/shape.txt",".././geometry/scripts/transformed.txt", "Cone");

    std::cout << "Cone drawn successfully!\n";
}

