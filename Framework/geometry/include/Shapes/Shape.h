#ifndef SHAPE_H
#define SHAPE_H

class Shape {
    public:
        virtual void draw()=0; 
        virtual ~Shape() {}
        //virtual vector<Triangle> getTriangles() = 0;
    };

#endif 
