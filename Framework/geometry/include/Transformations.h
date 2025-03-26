#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <vector>
#include <string>

class Transformations {
public:
    static void applyTransformation(const std::string& inputFile, const std::string& outputFile, int choice);
    
private:
    static std::vector<std::vector<double>> getTranslationMatrix(double tx, double ty, double tz);
    static std::vector<std::vector<double>> getRotationMatrix(double angle, char axis);
    static std::vector<std::vector<double>> getScalingMatrix(double sx, double sy, double sz);
};

#endif // TRANSFORMATIONS_H
