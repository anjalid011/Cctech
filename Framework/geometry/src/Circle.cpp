#include "Geometry.h"
#include "Transformations.h"
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

    int numTheta = 100;

    for (int i = 0; i <= numTheta; i++) {
        double theta = i * (2 * PI / numTheta);

        double x = radius * cos(theta);
        double y = radius * sin(theta);

        file << x << " " << y << "\n";
    }

    file.close();

    Transformations t;
    t.performTransformation();

    Plotter::plot2D("../geometry/scripts/circle.txt",".././geometry/scripts/transformed.txt", "Circle");
    std::cout << "Circle drawn successfully!\n";
}
