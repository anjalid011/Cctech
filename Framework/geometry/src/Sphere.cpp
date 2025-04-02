#include "Geometry.h"
#include "Plotter.h"
#include "Transformations.h"
#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.141592653589793

Sphere::Sphere(double r) : radius(r) {}

Sphere::Sphere(){
    radius=10;
}
void Sphere::draw() {
    double radius;
    std::cout << "Enter radius for Sphere: ";
    std::cin >> radius;
    Sphere sphere(radius);

    std::ofstream file(".././geometry/scripts/shape.txt");
    if (!file) {
        std::cerr << "Error: Unable to open sphere file!\n";
        return;
    }

    int numTheta = 50;  // Number of azimuthal divisions
    int numPhi = 50;    // Number of polar divisions

    for (int i = 0; i <= numTheta; i++) {
        double theta = i * (2 * PI / numTheta);
        for (int j = 0; j <= numPhi; j++) {
            double phi = j * (PI / numPhi);

            // Compute sphere coordinates using rotation matrix approach
            double x = radius * cos(theta) * sin(phi);
            double y = radius * sin(theta) * sin(phi);
            double z = radius * cos(phi);

            file << x << " " << y << " " << z << "\n";
        }
        file << "\n"; // Separate lines for better plotting
    }

    file.close();

    Transformations t;
    t.performTransformation();
    Plotter::plot3D(".././geometry/scripts/shape.txt","Sphere");
    //Plotter::plot3DTrans(".././geometry/scripts/shape.txt",".././geometry/scripts/transformed.txt", "Sphere");
    std::cout << "Sphere drawn successfully!\n";
}
