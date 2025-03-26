#ifndef PLOTTER_H
#define PLOTTER_H

#include <string>
#include <vector>

class Plotter {
public:
    static void plot2D(const std::string& filename, const std::string& transformedFile, const std::string& title);
    static void plot3D(const std::string& filename, const std::string& transformedFile, const std::string& title);
    static void savePoints(const std::string& filename, const std::vector<std::vector<double>>& points);
};

#endif // PLOTTER_H
