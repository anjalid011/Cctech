#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <Shapes/Shape.h>
#include <vector>
#include <QVector3D>
#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include "./Conversions/Triangle.h"

using namespace std;
typedef std::vector<vector<double>> Matrix;

class Line : public Shape {
private:
    double x1, y1, z1, x2, y2, z2;
    bool is3D;

public:
    Line(double x1, double y1, double x2, double y2);
    Line(double x1, double y1, double z1, double x2, double y2, double z2);
    void draw() override;
};

class Rectangle : public Shape {
private:
    double x, y, width, height;

public:
    Rectangle(double x, double y, double width, double height);
    void draw() override;
};

class Cuboid : public Shape {
private:
    double x, y, z, width, height, depth;

public:
    Cuboid(double x, double y, double z, double width, double height, double depth);
    void draw() override;
    Cuboid(); // Default constructor
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r);
    void draw() override;
};

class Sphere : public Shape {
private:
    double radius, centerX, centerY, centerZ; // Added center point variables

public:
    Sphere(double r, double cx, double cy, double cz); // Constructor with center point
    void draw() override;
};

class Cone : public Shape {
private:
    double radius, height, centerX, centerY, centerZ; // Added center point variables

public:
    Cone(double r, double h, double cx, double cy, double cz); // Constructor with center point
    void draw() override;
};

class Cylinder : public Shape {
private:
    double radius, height, centerX, centerY, centerZ; // Added center point variables

public:
    Cylinder(double r, double h, double cx, double cy, double cz); // Constructor with center point
    void draw() override;
};

struct Point3D {
    double x, y, z;
};

class Bezier3D : public Shape {
public:
    void inputControlPoints();
    void generateCurvePoints(int resolution);
    void saveToFile(const std::string& filename) const;
    void draw() override;
    void setControlPoints(const std::vector<Point3D>& points) {controlPoints = points;}
    

private:
    std::vector<Point3D> controlPoints;
    std::vector<Point3D> curvePoints;

    Point3D deCasteljau(double t) const;
};

#endif