#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <vector>
#include <string>
#include <cmath>

class Transformations {
public:
    // Constructor
    Transformations();

    // Load points into the class
    void loadPoints(const std::vector<std::vector<double>>& points);

    // Apply transformations
    void applyTranslation(double tx, double ty, double tz);
    void applyScaling(double sx, double sy, double sz);
    void applyRotation(double angle, char axis);

    // Get the transformed points
    std::vector<std::vector<double>> getTransformedPoints() const;

private:
    std::vector<std::vector<double>> points; // Stores the points of the shape

    // Helper methods
    std::vector<std::vector<double>> createRotationMatrix(double angle, char axis);
    std::vector<double> applyMatrixToPoint(const std::vector<std::vector<double>>& matrix, const std::vector<double>& point);
};

#endif // TRANSFORMATIONS_H