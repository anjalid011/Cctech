#ifndef RECTANGLE_H
#define RECTANGLE_H

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

#endif
