#include "Shapes/Geometry.h"
#include "Shapes/Plotter.h"
#include "Shapes/Shape.h"
#include "Shapes/Transformations.h"
#include <iostream>
#include <fstream>

Rectangle::Rectangle(double x, double y, double width, double height) 
    : x(x), y(y), width(width), height(height) {}

void Rectangle::draw() {
    std::ofstream rectFile(".././geometry/scripts/rectangle.dat");

    if (!rectFile) {
        std::cerr << "Error: Unable to open rectangle file!\n";
        return;
    }

    rectFile << x << " " << y << "\n";                        
    rectFile << x + width << " " << y << "\n";               
    rectFile << x + width << " " << y + height << "\n";      
    rectFile << x << " " << y + height << "\n";               
    rectFile << x << " " << y << "\n";                       

    rectFile.close();
    
    std::string stlFilePath = ".././geometry/scripts/rectangle.stl";
    std::string datFilePath = ".././geometry/scripts/rectangle.dat";

    // Transformations t;
    // t.performTransformation2D(".././geometry/scripts/rectangle.dat", ".././geometry/scripts/transformedRectangle.dat", "Rectangle");
    
    Plotter::plot2D("../geometry/scripts/rectangle.dat", "Rectangle");
    std::cout << "Rectangle drawn successfully!\n";
}
