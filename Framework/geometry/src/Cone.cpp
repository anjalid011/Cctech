#include "Geometry.h"
#include "Plotter.h"
#include "Transformations.h"
#include "StlToDat.h"
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
    // double radius, height;
    // std::cout << "Enter base radius and height for Cone: ";
    // std::cin >> radius >> height;

    std::ofstream stlFile("../geometry/scripts/cone.stl");
    std::ofstream datFile("../geometry/scripts/shape.dat");
    if (!stlFile || !datFile) {
        std::cerr << "Error: Unable to open STL or DAT file for Cone!\n";
        return;
    }

    stlFile << "solid Cone\n";

    int numTheta = 100; // Number of rotations
    int numT = 50;      // Points along the slanted line

    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        for (int j = 0; j < numT; j++) {
            double t1 = j * (1.0 / numT);
            double t2 = (j + 1) * (1.0 / numT);

            // Compute vertices for the current quad
            double x1 = radius * t1 * cos(theta1);
            double y1 = radius * t1 * sin(theta1);
            double z1 = height * (1 - t1);

            double x2 = radius * t1 * cos(theta2);
            double y2 = radius * t1 * sin(theta2);
            double z2 = height * (1 - t1);

            double x3 = radius * t2 * cos(theta2);
            double y3 = radius * t2 * sin(theta2);
            double z3 = height * (1 - t2);

            double x4 = radius * t2 * cos(theta1);
            double y4 = radius * t2 * sin(theta1);
            double z4 = height * (1 - t2);

            // Write two triangles for the current quad to the STL file
            stlFile << "  facet normal 0 0 0\n";
            stlFile << "    outer loop\n";
            stlFile << "      vertex " << x1 << " " << y1 << " " << z1 << "\n";
            stlFile << "      vertex " << x2 << " " << y2 << " " << z2 << "\n";
            stlFile << "      vertex " << x3 << " " << y3 << " " << z3 << "\n";
            stlFile << "    endloop\n";
            stlFile << "  endfacet\n";

            stlFile << "  facet normal 0 0 0\n";
            stlFile << "    outer loop\n";
            stlFile << "      vertex " << x1 << " " << y1 << " " << z1 << "\n";
            stlFile << "      vertex " << x3 << " " << y3 << " " << z3 << "\n";
            stlFile << "      vertex " << x4 << " " << y4 << " " << z4 << "\n";
            stlFile << "    endloop\n";
            stlFile << "  endfacet\n";
        }
    }

    // Write the base of the cone to the STL file
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        double x1 = radius * cos(theta1);
        double y1 = radius * sin(theta1);
        double z1 = 0;

        double x2 = radius * cos(theta2);
        double y2 = radius * sin(theta2);
        double z2 = 0;

        double x3 = 0;
        double y3 = 0;
        double z3 = 0;

        stlFile << "  facet normal 0 0 0\n";
        stlFile << "    outer loop\n";
        stlFile << "      vertex " << x1 << " " << y1 << " " << z1 << "\n";
        stlFile << "      vertex " << x2 << " " << y2 << " " << z2 << "\n";
        stlFile << "      vertex " << x3 << " " << y3 << " " << z3 << "\n";
        stlFile << "    endloop\n";
        stlFile << "  endfacet\n";
    }

    stlFile << "endsolid Cone\n";
    stlFile.close();
    datFile.close();

    std::string stlFilePath = ".././geometry/scripts/cone.stl";
    std::string datFilePath = ".././geometry/scripts/shape.dat";
    StlToDat s;
    s.convertSTLtoDAT(stlFilePath, datFilePath);

    Transformations t;
    t.performTransformation();
    Plotter::plot3D(".././geometry/scripts/shape.dat","Cone");
    std::cout << "Cone drawn successfully!\n";
}

