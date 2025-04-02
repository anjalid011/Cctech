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
    std::ofstream file(".././geometry/scripts/shape.txt");
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

    Transformations t;
    t.performTransformation();
    Plotter::plot3D(".././geometry/scripts/shape.txt","Cylinder");
    //Plotter::plot3DTrans(".././geometry/scripts/shape.txt",".././geometry/scripts/transformed.txt", "Cylinder");
    
}
