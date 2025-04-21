#include "Shapes/Geometry.h"
#include "Shapes/Shape.h"
#include "Shapes/Transformations.h"
#include <iostream>
#include <fstream>

Beizer::Beizer(){
   
}
void Beizer::draw() {
    std::ofstream file(".././geometry/scripts/beizer.dat");
    if (!file) {
        std::cerr << "Error: Unable to open beizer file!\n";
        return;
    }
    int t =100;
    vector<Point> temp = points;
    int n = points.size() - 1;
    for (int r = 1; r <= n; ++r) {
            for (int i = 0; i <= n - r; ++i) {
                file << temp[i].onXAxis = (1 - t) * temp[i].onXAxis + t * temp[i + 1].onXAxis << " "
                     << temp[i].onYAxis = (1 - t) * temp[i].onYAxis + t * temp[i + 1].onYAxis << "/n";
            }
        }
    file.close();
}

void Beizer::render(){

}
 
//Generate Bezier curve points
vector<Point> Beizer::generateCurve(int resolution) const {
    vector<Point> curvePoints;
    for (int i = 0; i <= resolution; ++i) {
        double t = (double)i / resolution;
        curvePoints.push_back(curve(t, controlPoints));
    }
    return curvePoints;
}