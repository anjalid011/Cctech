#ifndef PLOTTER_H
#define PLOTTER_H

#include <string>
#include <vector>

class Plotter {
public:
    static void plot2D(const std::string& filename, const std::string& transformedFile, const std::string& title);
    static void plot3D(const std::string& filename, const std::string& transformedFile, const std::string& title);
    static void savePoints(const std::string& filename, const std::vector<std::vector<double>>& points);
    void plotSphere(double x, double y, double z, double radius, const std::string& label);
    void plotCylinder(double x, double y, double z, double radius, double height, const std::string& label);
    void plotCone(double x, double y, double z, double radius, double height, const std::string& label);
    void plotCuboid(double x, double y, double z, double width, double depth, double height, const std::string& label);   
};

#endif // PLOTTER_H
