#include "Geometry.h"
#include "Plotter.h"
#include "Shape.h"
#include "Transformations.h"
#include <iostream>
#include <fstream>

Rectangle::Rectangle(double x, double y, double width, double height) 
    : x(x), y(y), width(width), height(height) {}

void Rectangle::draw() {
    std::ofstream rectFile(".././geometry/scripts/shape.dat");

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
    
    Transformations t;
    t.performTransformation2D();
    
    Plotter::plot2D("../geometry/scripts/shape.dat", "Rectangle");
    std::cout << "Rectangle drawn successfully!\n";
}
