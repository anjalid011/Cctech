#ifndef GEOMETRY_H
#define GEOMETRY_H

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
        double x, y, z, width, height, depth;
        bool isCube;
    
    public:
       
        Cuboid(double x, double y, double z, double width, double height, double depth);
        
        Cuboid(double x, double y, double z, double side);
    
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
        double radius;
    public:
        Sphere(double r);
        void draw() const;
};

class Cone {
    private:
        double radius, height;
    public:
        Cone(double r, double h);
        void draw() const;
};


#endif 
