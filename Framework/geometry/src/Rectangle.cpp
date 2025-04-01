#include "Geometry.h"
#include "Plotter.h"
#include <iostream>
#include <fstream>

Rectangle::Rectangle(double x, double y, double width, double height) 
    : x(x), y(y), width(width), height(height) {}

void Rectangle::draw() const {
    std::ofstream rectFile(".././geometry/scripts/rectangle.txt");

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

    Plotter::plot2D("../geometry/scripts/rectangle.txt",".././geometry/scripts/transformed.txt", "Rectangle");
    std::cout << "Rectangle drawn successfully!\n";
}
