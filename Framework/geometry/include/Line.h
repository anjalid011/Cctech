#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <fstream>

class Line {
private:
    double x1, y1, z1, x2, y2, z2;
    bool is3D;

public:
    Line(double x1, double y1, double x2, double y2);

    Line(double x1, double y1, double z1, double x2, double y2, double z2);

    void draw()const ;
};

#endif 
