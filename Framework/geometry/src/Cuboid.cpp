#include "Geometry.h"
#include "Shape.h"
#include "Plotter.h"
#include "Transformations.h"
#include "StlToDat.h"
#include <iostream>
#include <fstream>

using namespace std;

Cuboid::Cuboid(double x, double y, double z, double width, double height, double depth)
    : x(x), y(y), z(z), width(width), height(height), depth(depth) {}

Cuboid::Cuboid(){
    x=0;
    y=0;
    z=0;
    width=10;
    height=10;
    depth=10;
}

void Cuboid::draw() {
    std::cout << "Enter x, y, z, width, height, depth for Cuboid: ";
    std::cin >> x >> y >> z >> width >> height >> depth;

    std::ofstream stlFile(".././geometry/scripts/cuboid.stl");
    std::ofstream datFile(".././geometry/scripts/shape.dat");

    if (!stlFile) {
        std::cerr << "Error: Unable to open STL file for Cuboid!\n";
        return;
    }

    stlFile << "solid Cuboid\n";

    // Define the 8 vertices of the cuboid
    double A[3] = {x, y, z};
    double B[3] = {x + width, y, z};
    double C[3] = {x + width, y + height, z};
    double D[3] = {x, y + height, z};
    double E[3] = {x, y, z + depth};
    double F[3] = {x + width, y, z + depth};
    double G[3] = {x + width, y + height, z + depth};
    double H[3] = {x, y + height, z + depth};

    auto writeFacet = [&](double v1[3], double v2[3], double v3[3]) {
        stlFile << "  facet normal 0 0 0\n";
        stlFile << "    outer loop\n";
        stlFile << "      vertex " << v1[0] << " " << v1[1] << " " << v1[2] << "\n";
        stlFile << "      vertex " << v2[0] << " " << v2[1] << " " << v2[2] << "\n";
        stlFile << "      vertex " << v3[0] << " " << v3[1] << " " << v3[2] << "\n";
        stlFile << "    endloop\n";
        stlFile << "  endfacet\n";
    };

    // Front face
    writeFacet(A, B, C);
    writeFacet(A, C, D);

    // Back face
    writeFacet(E, F, G);
    writeFacet(E, G, H);

    // Left face
    writeFacet(A, D, H);
    writeFacet(A, H, E);

    // Right face
    writeFacet(B, C, G);
    writeFacet(B, G, F);

    // Top face
    writeFacet(D, C, G);
    writeFacet(D, G, H);

    // Bottom face
    writeFacet(A, B, F);
    writeFacet(A, F, E);

    stlFile << "endsolid Cuboid\n";

    stlFile.close();
    // datFile.close();

    std::cout << "Cuboid STL files created successfully!\n";
    std::string stlFilePath = ".././geometry/scripts/cuboid.stl";
    std::string datFilePath = ".././geometry/scripts/shape.dat";

    StlToDat s;
    s.convertSTLtoDAT(stlFilePath, datFilePath);

    Transformations t;
    t.performTransformation();

    Plotter::plot3D(".././geometry/scripts/shape.dat", "Cuboid");
}
