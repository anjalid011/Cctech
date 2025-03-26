#include "Transformations.h"
#include "Plotter.h"
#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.141592653589793

// **Function to apply the selected transformation**
void Transformations::applyTransformation(const std::string& inputFile, const std::string& outputFile, int choice) {
    std::ifstream input(inputFile);
    std::ofstream output(outputFile);
    
    if (!input || !output) {
        std::cerr << "Error: Unable to open input or output file!\n";
        return;
    }

    std::vector<std::vector<double>> transformationMatrix;
    
    if (choice == 1) { // Translation
        double tx, ty, tz;
        std::cout << "Enter translation values (tx, ty, tz): ";
        std::cin >> tx >> ty >> tz;
        transformationMatrix = getTranslationMatrix(tx, ty, tz);
    } 
    else if (choice == 2) { // Rotation
        double angle;
        char axis;
        std::cout << "Enter rotation angle (in degrees): ";
        std::cin >> angle;
        std::cout << "Enter axis of rotation (x/y/z): ";
        std::cin >> axis;
        transformationMatrix = getRotationMatrix(angle, axis);
    } 
    else if (choice == 3) { // Scaling
        double sx, sy, sz;
        std::cout << "Enter scaling factors (sx, sy, sz): ";
        std::cin >> sx >> sy >> sz;
        transformationMatrix = getScalingMatrix(sx, sy, sz);
    } 
    else {
        std::cerr << "Invalid choice!\n";
        return;
    }

    std::vector<std::vector<double>> originalPoints;
    std::vector<std::vector<double>> transformedPoints;
    double x, y, z;
    
    while (input >> x >> y) {
        z = 0;
        if (input.peek() != '\n' && input >> z) { } // Read Z if present

        std::vector<double> point = {x, y, z, 1}; // Homogeneous coordinates
        std::vector<double> newPoint(3, 0);

        for (int i = 0; i < 3; i++) {
            newPoint[i] = transformationMatrix[i][0] * point[0] + 
                          transformationMatrix[i][1] * point[1] + 
                          transformationMatrix[i][2] * point[2] + 
                          transformationMatrix[i][3] * point[3];
        }

        originalPoints.push_back({x, y, z});
        transformedPoints.push_back({newPoint[0], newPoint[1], newPoint[2]});
    }

    Plotter::savePoints(inputFile, originalPoints);
    Plotter::savePoints(outputFile, transformedPoints);
    
    // Plot both original and transformed shape
    if (transformedPoints[0].size() == 3)
        Plotter::plot3D(inputFile, outputFile, "Original & Transformed Shape");
    else
        Plotter::plot2D(inputFile, outputFile, "Original & Transformed Shape");
}

// **Function to create Translation Matrix**
std::vector<std::vector<double>> Transformations::getTranslationMatrix(double tx, double ty, double tz) {
    return {
        {1, 0, 0, tx},
        {0, 1, 0, ty},
        {0, 0, 1, tz},
        {0, 0, 0, 1}
    };
}

// **Function to create Rotation Matrix**
std::vector<std::vector<double>> Transformations::getRotationMatrix(double angle, char axis) {
    double radians = angle * PI / 180.0;
    if (axis == 'x' || axis == 'X') {
        return {
            {1, 0, 0, 0},
            {0, cos(radians), -sin(radians), 0},
            {0, sin(radians), cos(radians), 0},
            {0, 0, 0, 1}
        };
    } 
    else if (axis == 'y' || axis == 'Y') {
        return {
            {cos(radians), 0, sin(radians), 0},
            {0, 1, 0, 0},
            {-sin(radians), 0, cos(radians), 0},
            {0, 0, 0, 1}
        };
    } 
    else if (axis == 'z' || axis == 'Z') {
        return {
            {cos(radians), -sin(radians), 0, 0},
            {sin(radians), cos(radians), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
    }
    return {}; // Return empty matrix if invalid axis
}

// **Function to create Scaling Matrix**
std::vector<std::vector<double>> Transformations::getScalingMatrix(double sx, double sy, double sz) {
    return {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, 1}
    };
}
