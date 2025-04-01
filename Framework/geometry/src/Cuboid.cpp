#include "Geometry.h"
#include "Shape.h"
#include "Plotter.h"
#include "Transformations.h"
#include <iostream>
#include <fstream>

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
    Cuboid cuboid(x, y, z, width, height, depth);

    std::ofstream pointsFile(".././geometry/scripts/cuboid.txt");

    if (!pointsFile) {
        std::cerr << "Error: Unable to open points file!\n";
        return;
    }

    double A[3] = {x, y, z};
    double B[3] = {x + width, y, z};
    double C[3] = {x + width, y + height, z};
    double D[3] = {x, y + height, z};

    double E[3] = {x, y, z + depth};
    double F[3] = {x + width, y, z + depth};
    double G[3] = {x + width, y + height, z + depth};
    double H[3] = {x, y + height, z + depth};

    pointsFile << A[0] << " " << A[1] << " " << A[2] << "\n"
               << B[0] << " " << B[1] << " " << B[2] << "\n"
               << C[0] << " " << C[1] << " " << C[2] << "\n"
               << D[0] << " " << D[1] << " " << D[2] << "\n"
               << A[0] << " " << A[1] << " " << A[2] << "\n\n"

               << E[0] << " " << E[1] << " " << E[2] << "\n"
               << F[0] << " " << F[1] << " " << F[2] << "\n"
               << G[0] << " " << G[1] << " " << G[2] << "\n"
               << H[0] << " " << H[1] << " " << H[2] << "\n"
               << E[0] << " " << E[1] << " " << E[2] << "\n\n"

               << A[0] << " " << A[1] << " " << A[2] << "\n"
               << E[0] << " " << E[1] << " " << E[2] << "\n\n"

               << B[0] << " " << B[1] << " " << B[2] << "\n"
               << F[0] << " " << F[1] << " " << F[2] << "\n\n"

               << C[0] << " " << C[1] << " " << C[2] << "\n"
               << G[0] << " " << G[1] << " " << G[2] << "\n\n"

               << D[0] << " " << D[1] << " " << D[2] << "\n"
               << H[0] << " " << H[1] << " " << H[2] << "\n";

    pointsFile.close();
    Plotter::plot3D(".././geometry/scripts/cuboid.txt",".././geometry/scripts/transformed.txt", "Cuboid");

    std::cout << ("Cuboid") << " drawn successfully!\n";
}

void Cuboid::transformAndPlot() {
    std::string inputFile = ".././geometry/scripts/cuboid.txt";
    std::string outputFile = ".././geometry/scripts/transformed.txt";
    
    // Call performTransformation and Plotter::plot3D (assumed to be defined elsewhere)
    Transformations transformations;
    transformations.performTransformation(inputFile, outputFile);
    Plotter::plot3D(inputFile, outputFile, "Cuboid");
}