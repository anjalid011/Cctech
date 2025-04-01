#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <Shape.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

class Line {
private:
    double x1, y1, z1, x2, y2, z2;
    bool is3D;

public:
    Line(double x1, double y1, double x2, double y2);
    Line(double x1, double y1, double z1, double x2, double y2, double z2);
    void draw()const ;
};

class Rectangle {
    private:
        double x, y, width, height;
    
    public:
        Rectangle(double x, double y, double width, double height);
        virtual void draw() const;
};
    
class Cuboid : public Shape {
    private:
    double x, y, z, width, height, depth;
    public:
        std::vector<std::vector<double>> points; 
        Cuboid(double x, double y, double z, double width, double height, double depth);
        Cuboid(); 
        void draw() override;
        void transformAndPlot() override;
};

class Circle {
    private:
        double radius;
    public:
        Circle(double r);
        void draw() const;
};

class Sphere : public Shape {
    private:
        double radius;
    public:
        std::vector<std::vector<double>> points; 
        Sphere(double r);
        Sphere();
        void draw() override;
        void transformAndPlot() override;
};


class Cone : public Shape {
    private:
        double radius, height;
    public:
        Cone(double r, double h);
        Cone();
        void draw() override;
        void transformAndPlot() override;
        std::vector<std::vector<double>> points; 
};

class Cylinder : public Shape {
    private:
        double radius, height;
    public:
        Cylinder(double r, double h);
        void draw() override;
        Cylinder();
        void transformAndPlot() override;
        std::vector<std::vector<double>> points; 
    };


#endif 
