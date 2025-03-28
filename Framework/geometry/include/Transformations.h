#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <vector>
#include <string>

class Transformations {
public:
    // Constructor
    Transformations(const std::string& inputFile);

    // Apply user-defined transformation
    void applyTransformation(const std::vector<std::vector<double>>& matrix, const std::string& outputFile);

    // Specific transformations
    void applyTranslation(double tx, double ty, double tz, const std::string& outputFile);
    void applyScaling(double sx, double sy, double sz, const std::string& outputFile);
    void applyRotation(double angle, char axis, const std::string& outputFile);
    void applyMirroring(char axis, const std::string& outputFile);  // ✅ New function

private:
    std::vector<std::vector<double>> points;  // Stores the points of the shape
    void loadPoints(const std::string& inputFile);  // Read points from file
    void savePoints(const std::string& outputFile); // Save transformed points
};

#endif // TRANSFORMATIONS_H
