#ifndef ROBOT_H
#define ROBOT_H
#include "Robot.h"
#include "Geometry.h"
#include "Shape.h"
class Robot {
public:
    void buildAndPlot();
    Robot();
private:
    double torsoHeight, torsoRadius;
};

#endif // ROBOT_H
