#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "Shape.h"
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
    protected:
        double x, y, width, height;
    
    public:
        Rectangle(double x, double y, double width, double height);
        virtual void draw() const;
};
    
class Square : public Rectangle {
    public:
        Square(double x, double y, double side);
        void draw() const override;
};

class Cuboid {
    private:
        double x, y, z; // Center coordinates
        double width, depth, height;
        bool isCube;
    
    public:

        Cuboid(double x, double y, double z, double width, double depth, double height) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->width = width;
            this->depth = depth;
            this->height = height;
        }
    
        void draw() const;
};

class Circle {
    private:
        double radius;
    public:
        Circle(double r);
        void draw() const;
};

class Sphere {
    private:
        double x, y, z; // Center coordinates
        double radius;
    public:

        Sphere(double x, double y, double z, double r) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->radius = r;
        }
        void draw() const;
};

class Cone {
    private:
        double x, y, z; // Base center coordinates
        double radius;
        double height;
    public:

        Cone(double x, double y, double z, double radius, double height) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->radius = radius;
            this->height = height;
        }
        void draw() const;
};

class Cylinder {
    private:
        double x, y, z; // Base center coordinates
        double radius;
        double height;
    public:

        Cylinder(double x, double y, double z, double radius, double height) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->radius = radius;
            this->height = height;
        }
        void draw() const;
};


#endif 
