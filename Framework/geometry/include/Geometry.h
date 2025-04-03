#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <Shape.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include<bits/stdc++.h>

using namespace std;
typedef std::vector<vector<double>>  Matrix;
class Line : public Shape {
private:
    double x1, y1, z1, x2, y2, z2;
    bool is3D;

public:
    Line(double x1, double y1, double x2, double y2);
    Line(double x1, double y1, double z1, double x2, double y2, double z2);
    void draw() override ;
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
        Matrix points; 
        Cuboid(double x, double y, double z, double width, double height, double depth);
        void draw() override;
        Cuboid();
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
        double radius;
    public:
        Matrix points; 
        Sphere(double r);
        void draw() override;
        Sphere();
};


class Cone : public Shape {
    private:
        double radius, height;
    public:
        Cone(double r, double h);
        void draw() override;
        Matrix points;
        Cone(); 
};

class Cylinder : public Shape {
    private:
        double radius, height;
    public:
        Cylinder(double r, double h);
        void draw() override;
        Matrix points; 
        Cylinder();
    };


#endif 
