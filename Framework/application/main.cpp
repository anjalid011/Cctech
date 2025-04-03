#include "Geometry.h"
#include "Transformations.h"
#include "Robot.h"
#include "Plotter.h"
#include "ObjToStl.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

using namespace std;

std::shared_ptr<Shape> getShape(int choice) {
    // Map of functions to handle input for each shape
    std::unordered_map<int, std::function<std::shared_ptr<Shape>()>> shapeInputHandlers = {
        {1, []() -> std::shared_ptr<Shape> {
            // Input for Cuboid
            double cuboidX, cuboidY, cuboidZ, cuboidWidth, cuboidHeight, cuboidDepth;
            std::cout << "Enter x, y, z, width, height, depth for Cuboid: ";
            std::cin >> cuboidX >> cuboidY >> cuboidZ >> cuboidWidth >> cuboidHeight >> cuboidDepth;
            return std::make_shared<Cuboid>(cuboidX, cuboidY, cuboidZ, cuboidWidth, cuboidHeight, cuboidDepth);
        }},
        {2, []() -> std::shared_ptr<Shape> {
            // Input for Sphere
            double sphereRadius;
            std::cout << "Enter radius for Sphere: ";
            std::cin >> sphereRadius;
            return std::make_shared<Sphere>(sphereRadius);
        }},
        {3, []() -> std::shared_ptr<Shape> {
            // Input for Cone
            double coneBaseRadius, coneHeight;
            std::cout << "Enter base radius and height for Cone: ";
            std::cin >> coneBaseRadius >> coneHeight;
            return std::make_shared<Cone>(coneBaseRadius, coneHeight);
        }},
        {4, []() -> std::shared_ptr<Shape> {
            // Input for Cylinder
            double cylinderRadius, cylinderHeight;
            std::cout << "Enter radius and height for Cylinder: ";
            std::cin >> cylinderRadius >> cylinderHeight;
            return std::make_shared<Cylinder>(cylinderRadius, cylinderHeight);
        }},
        {5, []() -> std::shared_ptr<Shape> {
            // double torsoHeight, torsoRadius;
            // std::cout << "Enter torso height: ";
            // std::cin >> torsoHeight;
            // std::cout << "Enter torso radius: ";
            // std::cin >> torsoRadius;
            Robot r;
            r.buildAndPlot();
            return nullptr; // No shape to return for Robot
        }},
        {6, []() -> std::shared_ptr<Shape> {
            double x1, y1, x2, y2;
            std::cout << "Enter x1, y1, x2, y2 for 2D Line: ";
            std::cin >> x1 >> y1 >> x2 >> y2;
            Line line(x1, y1, x2, y2);
            line.draw();
            return std::make_shared<Line>(x1, y1, x2, y2);
        }},
        {7, []() -> std::shared_ptr<Shape> {
            double x1, y1, z1, x2, y2, z2;
            std::cout << "Enter x1, y1, z1, x2, y2, z2 for 3D Line: ";
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            Line line(x1, y1, z1, x2, y2, z2); 
            return std::make_shared<Line>(x1, y1, z1, x2, y2, z2);
        }},
        {8, []() -> std::shared_ptr<Shape> {
            double x, y, width, height;
            std::cout << "Enter x, y, width, height for Rectangle: ";
            std::cin >> x >> y >> width >> height;
            Rectangle rectangle(x, y, width, height);
            return std::make_shared<Rectangle>(x, y, width, height);
        }},
        {9, []() -> std::shared_ptr<Shape> {
            double radius;
            std::cout << "Enter radius for Circle: ";
            std::cin >> radius;
            Circle circle(radius);
            return std::make_shared<Circle>(radius);
        }}
    };

    // Call the appropriate input handler based on the choice
    if (shapeInputHandlers.find(choice) != shapeInputHandlers.end()) {
        return shapeInputHandlers[choice]();
    }

    return nullptr; // Return nullptr if the choice is invalid
}
int main() {
    int choice;
    std::cout << "Choose a shape to plot:\n";
    std::cout << "1. Cuboid\n2. Sphere\n3. Cone\n4. Cylinder\n5. Robot\n6. 2D Line\n7. 3D line\n8. Rectangle\n9. Circle\n10. ObjToStl";
    std::cout << "\nEnter choice: ";
    std::cin >> choice;

    if (choice >= 1 && choice <= 9) {
        // Get the shape based on the user's choice
        std::shared_ptr<Shape> shape = getShape(choice);
        if (shape) {
            shape->draw();
        } else {
            std::cout << "Invalid choice!\n";
        }
    }else if(choice==10){
        ObjToStl o;
        o.ConvertObjToStl();
    } else {
        std::cout << "Invalid choice!\n";
    }
   
    return 0;
}

