#include "Shapes/Geometry.h"
#include "Shapes/Plotter.h"
#include "Shapes/Shape.h"
#include "Shapes/Transformations.h"
#include <iostream>
#include <fstream>

using namespace std;
Line::Line(double x1, double y1, double x2, double y2) 
    : x1(x1), y1(y1), z1(0), x2(x2), y2(y2), z2(0), is3D(false) {}

Line::Line(double x1, double y1, double z1, double x2, double y2, double z2) 
    : x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2), is3D(true) {}

void Line::draw() {
    std::ofstream pointsFile(".././geometry/scripts/line.dat");

    if (!pointsFile) {
        std::cerr << "Error: Unable to open points file!\n";
        return;
    }

    for (int i = 0; i < 10; i++) {
        double t = i / 9.0;
        double px = x1 + t * (x2 - x1);
        double py = y1 + t * (y2 - y1);
        if (is3D) {
            double pz = z1 + t * (z2 - z1);
            pointsFile << px << " " << py << " " << pz << "\n";
        } else {
            pointsFile << px << " " << py << "\n";
        }
    }
    pointsFile.close();

    // Transformations t;
    // t.performTransformation2D(".././geometry/scripts/line.dat", ".././geometry/scripts/transformedLine.dat", "Line");
    
    Plotter::plot2D("../geometry/scripts/line.dat", "Line");
    std::cout << (is3D ? "3D" : "2D") << " Line drawn successful!\n";

}
