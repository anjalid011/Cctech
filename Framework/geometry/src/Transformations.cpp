#include "Transformations.h"
#include "Plotter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#define PI 3.14159265358979323846

Transformations::Transformations(const std::string& inputFile) {
    loadPoints(inputFile);
}

void Transformations::loadPoints(const std::string& inputFile) {
    std::ifstream file(inputFile);
    if (!file) {
        std::cerr << "Error: Unable to open file " << inputFile << "\n";
        return;
    }

    double x, y, z;
    while (file >> x >> y >> z) {
        points.push_back({x, y, z});
    }
    file.close();
}

void Transformations::applyTransformation(const std::vector<std::vector<double>>& matrix, const std::string& outputFile) {
    std::vector<std::vector<double>> transformedPoints;

    for (const auto& point : points) {
        std::vector<double> newPoint(3, 0);
        for (int i = 0; i < 3; ++i) {
            newPoint[i] = matrix[i][0] * point[0] + matrix[i][1] * point[1] + matrix[i][2] * point[2];
        }
        transformedPoints.push_back(newPoint);
    }

    points = transformedPoints;
    savePoints(outputFile);
}

void Transformations::applyTranslation(double tx, double ty, double tz, const std::string& outputFile) {
    for (auto& point : points) {
        point[0] += tx;
        point[1] += ty;
        point[2] += tz;
    }
    savePoints(outputFile);
    Plotter::plot3DTrans(".././geometry/scripts/shape.txt",".././geometry/scripts/transformed.txt","Shape");
}

void Transformations::applyScaling(double sx, double sy, double sz, const std::string& outputFile) {
    for (auto& point : points) {
        point[0] *= sx;
        point[1] *= sy;
        point[2] *= sz;
    }
    savePoints(outputFile);
    Plotter::plot3DTrans(".././geometry/scripts/shape.txt",".././geometry/scripts/transformed.txt","Shape");
}

void Transformations::applyRotation(double angle, char axis, const std::string& outputFile) {
    double rad = angle * PI / 180.0;
    std::vector<std::vector<double>> rotationMatrix(3, std::vector<double>(3, 0));

    if (axis == 'x') {
        rotationMatrix = {
            {1, 0, 0},
            {0, cos(rad), -sin(rad)},
            {0, sin(rad), cos(rad)}
        };
    } else if (axis == 'y') {
        rotationMatrix = {
            {cos(rad), 0, sin(rad)},
            {0, 1, 0},
            {-sin(rad), 0, cos(rad)}
        };
    } else if (axis == 'z') {
        rotationMatrix = {
            {cos(rad), -sin(rad), 0},
            {sin(rad), cos(rad), 0},
            {0, 0, 1}
        };
    }

    applyTransformation(rotationMatrix, outputFile);
    Plotter::plot3DTrans(".././geometry/scripts/shape.txt",".././geometry/scripts/transformed.txt", "Shape");
}

void Transformations::savePoints(const std::string& outputFile) {
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
void Transformations::performTransformation() {
    int choice;
    std::string inputFile = ".././geometry/scripts/shape.txt";
    std::string outputFile = ".././geometry/scripts/transformed.txt";
    std::cout << "Choose a transformation:\n";
    std::cout << "1. Translation\n2. Scaling\n3. Rotation\n 4.NO\n Enter choice: ";
    std::cin >> choice;

    Transformations transform(inputFile);

    if (choice == 1) {
        double tx, ty, tz;
        std::cout << "Enter translation (tx ty tz): ";
        std::cin >> tx >> ty >> tz;
        transform.applyTranslation(tx, ty, tz, outputFile);
    } 
    else if (choice == 2) {
        double sx, sy, sz;
        std::cout << "Enter scaling factors (sx sy sz): ";
        std::cin >> sx >> sy >> sz;
        transform.applyScaling(sx, sy, sz, outputFile);
    } 
    else if (choice == 3) {
        double angle;
        char axis;
        std::cout << "Enter rotation angle (degrees) and axis (x/y/z): ";
        std::cin >> angle >> axis;
        transform.applyRotation(angle, axis, outputFile);
    } 
    

}
