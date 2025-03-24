#ifndef CUBOID_H
#define CUBOID_H

class Cuboid {
private:
    double x, y, z, width, height, depth;
    bool isCube;

public:
    // Constructor for Cuboid
    Cuboid(double x, double y, double z, double width, double height, double depth);
    
    // Constructor for Cube (special case of Cuboid)
    Cuboid(double x, double y, double z, double side);

    void draw() const;
};

#endif
