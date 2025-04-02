#include "Geometry.h"
#include "Plotter.h"
#include "Transformations.h"
#include "StlToDat.h"
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
    std::cout << "Enter radius and height for Cylinder: ";
    std::cin >> radius >> height;

    std::ofstream stlFile(".././geometry/scripts/cylinder.stl");
    std::ofstream datFile(".././geometry/scripts/shape.dat");

    if (!stlFile || !datFile) {
        std::cerr << "Error: Unable to open STL or DAT file for Cylinder!\n";
        return;
    }

    stlFile << "solid Cylinder\n";

    int numTheta = 100; // Number of angular divisions
    int numT = 50;      // Number of height divisions

    // Generate the lateral surface of the cylinder
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        for (int j = 0; j < numT; j++) {
            double t1 = j * (1.0 / numT);
            double t2 = (j + 1) * (1.0 / numT);

            // Compute the four vertices of the current quad
            double x1 = radius * cos(theta1);
            double y1 = radius * sin(theta1);
            double z1 = height * t1;

            double x2 = radius * cos(theta2);
            double y2 = radius * sin(theta2);
            double z2 = height * t1;

            double x3 = radius * cos(theta2);
            double y3 = radius * sin(theta2);
            double z3 = height * t2;

            double x4 = radius * cos(theta1);
            double y4 = radius * sin(theta1);
            double z4 = height * t2;

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

    // Generate the top and bottom faces of the cylinder
    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);

        // Bottom face
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

        // Top face
        double x4 = radius * cos(theta1);
        double y4 = radius * sin(theta1);
        double z4 = height;

        double x5 = radius * cos(theta2);
        double y5 = radius * sin(theta2);
        double z5 = height;

        double x6 = 0;
        double y6 = 0;
        double z6 = height;

        stlFile << "  facet normal 0 0 0\n";
        stlFile << "    outer loop\n";
        stlFile << "      vertex " << x4 << " " << y4 << " " << z4 << "\n";
        stlFile << "      vertex " << x5 << " " << y5 << " " << z5 << "\n";
        stlFile << "      vertex " << x6 << " " << y6 << " " << z6 << "\n";
        stlFile << "    endloop\n";
        stlFile << "  endfacet\n";
    }

    stlFile << "endsolid Cylinder\n";

    stlFile.close();
    datFile.close();

    std::cout << "Cylinder STL and DAT files created successfully!\n";
    std::string stlFilePath = ".././geometry/scripts/cylinder.stl";
    std::string datFilePath = ".././geometry/scripts/shape.dat";

    StlToDat s;
    s.convertSTLtoDAT(stlFilePath, datFilePath);

    Transformations t;
    t.performTransformation();

    Plotter::plot3D(".././geometry/scripts/shape.dat", "Cylinder");
}