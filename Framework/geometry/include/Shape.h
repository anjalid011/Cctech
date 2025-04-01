#ifndef SHAPE_H
#define SHAPE_H

class Shape {
    public:
        virtual void draw() = 0;
        virtual void transformAndPlot() = 0;  
        virtual ~Shape() {}
    };

#endif 
