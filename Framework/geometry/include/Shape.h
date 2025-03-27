#ifndef SHAPE_H
#define SHAPE_H

#include <string>

class Shape {
public:
    virtual ~Shape() {} // Virtual destructor
    virtual void draw() const = 0; // Pure virtual function to enforce draw() in derived classes
    virtual std::string getFilename() const = 0; // Returns the filename containing shape points
};

#endif
