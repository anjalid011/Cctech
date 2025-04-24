#include "Shapes/Transformations.h"

// Constructor
Transformations::Transformations() {}

// Load points into the class
void Transformations::loadPoints(const std::vector<std::vector<double>>& newPoints) {
    points = newPoints;
}

// Apply translation to the points
void Transformations::applyTranslation(double tx, double ty, double tz) {
    for (auto& point : points) {
        point[0] += tx;
        point[1] += ty;
        point[2] += tz;
    }
}

// Apply scaling to the points
void Transformations::applyScaling(double sx, double sy, double sz) {
    for (auto& point : points) {
        point[0] *= sx;
        point[1] *= sy;
        point[2] *= sz;
    }
}

// Apply rotation to the points around a specified axis
void Transformations::applyRotation(double angle, char axis) {
    double rad = angle * M_PI / 180.0; // Convert angle to radians
    auto rotationMatrix = createRotationMatrix(rad, axis);

    for (auto& point : points) {
        point = applyMatrixToPoint(rotationMatrix, point);
    }
}

// Get the transformed points
std::vector<std::vector<double>> Transformations::getTransformedPoints() const {
    return points;
}

// Create a rotation matrix for a given angle and axis
std::vector<std::vector<double>> Transformations::createRotationMatrix(double angle, char axis) {
    std::vector<std::vector<double>> matrix(3, std::vector<double>(3, 0));

    if (axis == 'x') {
        matrix = {
            {1, 0, 0},
            {0, cos(angle), -sin(angle)},
            {0, sin(angle), cos(angle)}
        };
    } else if (axis == 'y') {
        matrix = {
            {cos(angle), 0, sin(angle)},
            {0, 1, 0},
            {-sin(angle), 0, cos(angle)}
        };
    } else if (axis == 'z') {
        matrix = {
            {cos(angle), -sin(angle), 0},
            {sin(angle), cos(angle), 0},
            {0, 0, 1}
        };
    }

    return matrix;
}

// Apply a transformation matrix to a single point
std::vector<double> Transformations::applyMatrixToPoint(const std::vector<std::vector<double>>& matrix, const std::vector<double>& point) {
    std::vector<double> result(3, 0);

    for (int i = 0; i < 3; ++i) {
        result[i] = matrix[i][0] * point[0] + matrix[i][1] * point[1] + matrix[i][2] * point[2];
    }

    return result;
}