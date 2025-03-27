
#include "Geometry.h"
#include "Plotter.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>  // For mkdir
#include <sys/types.h> // For mkdir

using namespace std;
Line::Line(double x1, double y1, double x2, double y2) 
    : x1(x1), y1(y1), z1(0), x2(x2), y2(y2), z2(0), is3D(false) {}

Line::Line(double x1, double y1, double z1, double x2, double y2, double z2) 
    : x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2), is3D(true) {}

void Line::draw() const {
    // struct stat st;
    // if (stat("geometry/scripts", &st) != 0) {
    //     if (mkdir("geometry/scripts", 0777) != 0) {
    //         std::cerr << "Error: Failed to create directory 'geometry/scripts'!\n";
    //         return;
    //     }
    // }

    std::ofstream pointsFile(".././geometry/scripts/points.txt");

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

    // if (is3D) {
    //     Plotter::plot3D(".././geometry/scripts/points.txt",".././geometry/scripts/transformed.txt", "3D Line");

    // } else {
    //     Plotter::plot2D(".././geometry/scripts/points.txt",".././geometry/scripts/transformed.txt", "2D Line");

    // }

    std::cout << (is3D ? "3D" : "2D") << " Line drawn successful!\n";

}
