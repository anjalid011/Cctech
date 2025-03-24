#ifndef CUBOID_H
#define CUBOID_H

class Cuboid {
private:
    double x, y, z, width, height, depth;
    bool isCube;

public:
   
    Cuboid(double x, double y, double z, double width, double height, double depth);
    
    Cuboid(double x, double y, double z, double side);

    void draw() const;
};

#endif
