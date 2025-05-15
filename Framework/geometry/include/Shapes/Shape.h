#ifndef SHAPE_H
#define SHAPE_H
#include <string>
class Shape {
    public:
        float translationX = 0.0f;
        float translationY = 0.0f;
        float translationZ = 0.0f;
        
        virtual void draw()=0; 
        virtual std::string getType() const = 0;
        virtual ~Shape() {}
        //virtual vector<Triangle> getTriangles() = 0;
};

#endif 