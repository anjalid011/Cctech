#include "Shapes/Geometry.h"
#include "Shapes/Transformations.h"
#include "Shapes/Plotter.h"
#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.141592653589793

Circle::Circle(double r) : radius(r) {}

void Circle::draw() {
    std::ofstream file(".././geometry/scripts/circle.stl");
    if (!file) {
        std::cerr << "Error: Unable to open circle file!\n";
        return;
    }

    int numTheta = 100;

    for (int i = 0; i <= numTheta; i++) {
        double theta = i * (2 * PI / numTheta);

        double x = radius * cos(theta);
        double y = radius * sin(theta);

        file << x << " " << y << "\n";
    }

    file.close();

    std::string stlFilePath = ".././geometry/scripts/circle.stl";
    std::string datFilePath = ".././geometry/scripts/circle.dat";

    // Transformations t;
    // t.performTransformation2D(".././geometry/scripts/circle.dat", ".././geometry/scripts/transformedCircle.dat", "Circle");

    Plotter::plot2D("../geometry/scripts/circle.dat", "Circle");
    std::cout << "Circle drawn successfully!\n";
}
