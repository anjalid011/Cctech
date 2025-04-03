#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
class Transformations {
public:
    // Constructor
    Transformations(const std::string& inputFile);
    Transformations() = default;    

    // Apply user-defined transformation
    void applyTransformation(const std::vector<std::vector<double>>& matrix, const std::string& outputFile);
    void applyTranslation(double tx, double ty, double tz, const std::string& outputFile);
    void applyScaling(double sx, double sy, double sz, const std::string& outputFile);
    void applyRotation(double angle, char axis, const std::string& outputFile);
    void applyTranslation2D(double tx, double ty, const std::string& outputFile);
    void applyScaling2D(double sx, double sy, const std::string& outputFile);
    void applyRotation2D(double angle, const std::string& outputFile);
    void performTransformation();
    void performTransformation2D();


private:
    std::vector<std::vector<double>> points;  // Stores the points of the shape
    void loadPoints(const std::string& inputFile);  // Read points from file
    void savePoints(const std::string& outputFile); // Save transformed points
};

#endif // TRANSFORMATIONS_H
