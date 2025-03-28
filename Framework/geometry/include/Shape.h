#ifndef SHAPE_H
#define SHAPE_H
#include <vector>
#include <string>

class Shape {
    protected:
        std::vector<std::vector<double>> points;  // Stores shape's points
        std::string shapeFile;  // File where shape data is stored
    
    public:
        virtual void generate() = 0;  // Pure virtual function to generate shape
        virtual void saveToFile(const std::string& filename);
        std::vector<std::vector<double>> getPoints();  // Getter for points
};
#endif
