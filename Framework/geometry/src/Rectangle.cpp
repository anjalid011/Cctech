#include "Rectangle.h"
#include <iostream>
#include <fstream>

Rectangle::Rectangle(double x, double y, double width, double height) 
    : x(x), y(y), width(width), height(height) {}

void Rectangle::draw() const {
    std::ofstream rectFile(".././geometry/scripts/rectangle.txt");
    FILE *gnuplot = popen("gnuplot -persist", "w");

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

    fprintf(gnuplot, "set terminal wxt\n");
    fprintf(gnuplot, "set mouse\n");
    fprintf(gnuplot, "set xlabel 'X-axis'\n");
    fprintf(gnuplot, "set ylabel 'Y-axis'\n");
    fprintf(gnuplot, "plot '.././geometry/scripts/rectangle.txt' using 1:2 with lines lw 2 title 'Rectangle', \\\n");
    fprintf(gnuplot, "     '.././geometry/scripts/rectangle.txt' using 1:2 with points pt 7 ps 1.5 lc rgb 'red'\n");

    pclose(gnuplot);
    std::cout << "Rectangle drawn successfully!\n";
}
Square::Square(double x, double y, double side)
    : Rectangle(x, y, side, side) {}

void Square::draw() const {
    std::cout << "Drawing Square...\n";
    Rectangle::draw(); 
}
