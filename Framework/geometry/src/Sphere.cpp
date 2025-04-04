#include "Geometry.h"
#include "Plotter.h"
#include "Transformations.h"
#include "StlToDat.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "Triangle.h"

#define PI 3.141592653589793

Sphere::Sphere(double r) : radius(r) {}

Sphere::Sphere(){
    radius=10;
}
void Sphere::draw() {
    // double radius;
    // std::cout << "Enter radius for Sphere: ";
    // std::cin >> radius;

    std::ofstream stlFile(".././geometry/scripts/sphere.stl");
    std::ofstream datFile(".././geometry/scripts/shape.dat"); // Open DAT file
    if (!stlFile || !datFile) {
        std::cerr << "Error: Unable to open STL or DAT file!\n";
        return;
    }

    stlFile << "solid Sphere\n";

    int numTheta = 50;  // Number of azimuthal divisions
    int numPhi = 50;    // Number of polar divisions

    vector<Triangle> triangles;

    for (int i = 0; i < numTheta; i++) {
        double theta1 = i * (2 * PI / numTheta);
        double theta2 = (i + 1) * (2 * PI / numTheta);


        for (int j = 0; j < numPhi; j++) {
            double phi1 = j * (PI / numPhi);
            double phi2 = (j + 1) * (PI / numPhi);

            // Compute the four vertices of the current quad
            double x1 = radius * cos(theta1) * sin(phi1);
            double y1 = radius * sin(theta1) * sin(phi1);
            double z1 = radius * cos(phi1);
            Vec3 v1(x1, y1, z1);

            double x2 = radius * cos(theta2) * sin(phi1);
            double y2 = radius * sin(theta2) * sin(phi1);
            double z2 = radius * cos(phi1);
            Vec3 v2(x2, y2, z2);

            double x3 = radius * cos(theta2) * sin(phi2);
            double y3 = radius * sin(theta2) * sin(phi2);
            double z3 = radius * cos(phi2);
            Vec3 v3(x3, y3, z3);

            double x4 = radius * cos(theta1) * sin(phi2);
            double y4 = radius * sin(theta1) * sin(phi2);
            double z4 = radius * cos(phi2);
            Vec3 v4(x4, y4, z4);

            Triangle t1(v1, v2, v3);
            Triangle t2(v1, v3, v4);

            triangles.push_back(t1);
            triangles.push_back(t2);
        }
    }

    for(auto& t : triangles) {
        auto v1 = t.v1;
        auto v2 = t.v2;
        auto v3 = t.v3;
        auto normal = t.normal;

        // Write two triangles for the current quad to the STL file
        stlFile << "  facet normal " << normal.x << " " << normal.y << " " << normal.z << "\n";
        stlFile << "    outer loop\n";
        stlFile << "      vertex " << v1.x << " " << v1.y << " " << v1.z << "\n";
        stlFile << "      vertex " << v2.x << " " << v2.y << " " << v2.z << "\n";
        stlFile << "      vertex " << v3.x << " " << v3.y << " " << v3.z << "\n";
        stlFile << "    endloop\n";
        stlFile << "  endfacet\n";
    }

    stlFile << "endsolid Sphere\n";
    stlFile.close();
    datFile.close();

    std::string stlFilePath = ".././geometry/scripts/sphere.stl";
    std::string datFilePath = ".././geometry/scripts/shape.dat";

    StlToDat s;
    s.convertSTLtoDAT(stlFilePath, datFilePath);

    Transformations t;
    t.performTransformation();
    
    Plotter::plot3D(".././geometry/scripts/shape.dat","Sphere");
    std::cout << "Sphere STL and DAT files created successfully!\n";
}