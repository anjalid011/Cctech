#include "Geometry.h"
#include "Plotter.h"
#include <iostream>
#include <fstream>

Cuboid::Cuboid(double x, double y, double z, double width, double height, double depth)
    : x(x), y(y), z(z), width(width), height(height), depth(depth), isCube(false) {}

Cuboid::Cuboid(double x, double y, double z, double side)
    : x(x), y(y), z(z), width(side), height(side), depth(side), isCube(true) {}


void Cuboid::draw() const {
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
    std::cout << (isCube ? "Cube" : "Cuboid") << " drawn successfully!\n";
}
void Cuboid::savePoints(const std::string& outputFile) {
    std::ofstream file(outputFile);
    if (!file) {
        std::cerr << "Error: Unable to create file " << outputFile << "\n";
        return;
    }

    for (const auto& point : points) {
        file << point[0] << " " << point[1] << " " << point[2] << "\n";
    }
    file.close();
}
