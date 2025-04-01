#include "Geometry.h"
#include "Plotter.h"
#include "Transformations.h"
#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.141592653589793

Cylinder::Cylinder(double r, double h) : radius(r), height(h) {}

Cylinder::Cylinder(){
    radius=10;
    height=10;
}
void Cylinder::draw() {
    std::ofstream file(".././geometry/scripts/cylinder.txt");
    if (!file) {
        std::cerr << "Error: Unable to open cylinder file!\n";
        return;
    }

    int numTheta = 100;
    int numT = 50;   

    for (int i = 0; i <= numTheta; i++) {
        double theta = i * (2 * PI / numTheta);

        for (int j = 0; j <= numT; j++) {
            double t = j * (1.0 / numT);
        
            double x = radius * cos(theta);
            double y = radius * sin(theta);
            double z = height * t;

            file << x << " " << y << " " << z << "\n";
        }
        file << "\n"; 
    }

    file.close();
    std::cout << "Cylinder drawn successfully!\n";
}

void Cylinder::transformAndPlot() {
    std::string inputFile = ".././geometry/scripts/cone.txt";
    std::string outputFile = ".././geometry/scripts/transformed.txt";
    
    // Call performTransformation and Plotter::plot3D (assumed to be defined elsewhere)
    Transformations transformations;
    transformations.performTransformation(inputFile, outputFile);
    Plotter::plot3D(inputFile, outputFile, "Cylinder");
}