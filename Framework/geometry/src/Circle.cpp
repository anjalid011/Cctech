#include "Geometry.h"
#include "Plotter.h"
#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.141592653589793

Circle::Circle(double r) : radius(r) {}

void Circle::draw() const {
    std::ofstream file(".././geometry/scripts/circle.txt");
    if (!file) {
        std::cerr << "Error: Unable to open circle file!\n";
        return;
    }

    int numTheta = 100; // More points for smoother circle

    for (int i = 0; i <= numTheta; i++) {
        double theta = i * (2 * PI / numTheta);

        // Compute circle coordinates by rotating a line
        double x = radius * cos(theta);
        double y = radius * sin(theta);

        file << x << " " << y << "\n";
    }

    file.close();

    //Plotter::plot2D("../geometry/scripts/circle.txt",".././geometry/scripts/transformed.txt", "Circle");
    std::cout << "Circle drawn successfully!\n";
}
