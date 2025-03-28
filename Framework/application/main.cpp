#include "Geometry.h"
#include "Transformations.h"
#include <iostream>
#include "Plotter.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Transformations.h"
#include "Shape.h"

void performTransformation(const std::string& inputFile, const std::string& outputFile) {
    int choice;
    std::cout << "Choose a transformation:\n";
    std::cout << "1. Translation\n2. Scaling\n3. Rotation\nEnter choice: ";
    std::cin >> choice;

    Transformations transform(inputFile);

    if (choice == 1) {
        double tx, ty, tz;
        std::cout << "Enter translation (tx ty tz): ";
        std::cin >> tx >> ty >> tz;
        transform.applyTranslation(tx, ty, tz, outputFile);
    } else if (choice == 2) {
        double sx, sy, sz;
        std::cout << "Enter scaling factors (sx sy sz): ";
        std::cin >> sx >> sy >> sz;
        transform.applyScaling(sx, sy, sz, outputFile);
    } else if (choice == 3) {
        double angle;
        char axis;
        std::cout << "Enter rotation angle (degrees) and axis (x/y/z): ";
        std::cin >> angle >> axis;
        transform.applyRotation(angle, axis, outputFile);
    } else {
        std::cout << "Invalid choice!\n";
        return;
    }

    std::cout << "Transformation applied successfully!\n";
}

void createRobot() {
    Plotter plotter;
    
    // Head
    plotter.plotSphere(0, 55, 0, 10, "Head");
    
    // Hat
    plotter.plotCone(0, 65, 0, 10, 20, "Hat");
    
    // Neck
    plotter.plotCylinder(0, 50, 0, 5, 5, "Neck");
    
    // Torso + Hips (Body)
    plotter.plotCylinder(0, 30, 0, 15, 40, "Body");
    
    // Shoulder Joints
    plotter.plotSphere(-15, 47, 0, 2.5, "Left Shoulder Joint");
    plotter.plotSphere(15, 47, 0, 2.5, "Right Shoulder Joint");
    
    // Upper Arms
    plotter.plotCylinder(-20, 35, 0, 2.5, 21, "Left Upper Arm");
    plotter.plotCylinder(20, 35, 0, 2.5, 21, "Right Upper Arm");
    
    // Elbows
    plotter.plotSphere(-30, 25, 0, 2.5, "Left Elbow");
    plotter.plotSphere(30, 25, 0, 2.5, "Right Elbow");
    
    // Lower Arms
    plotter.plotCylinder(-35, 15, 0, 2.5, 20, "Left Lower Arm");
    plotter.plotCylinder(35, 15, 0, 2.5, 20, "Right Lower Arm");
    
    // Hands
    plotter.plotCuboid(-40, 5, 0, 4, 5, 5, "Left Hand");
    plotter.plotCuboid(40, 5, 0, 4, 5, 5, "Right Hand");
    
    // Hip Joints
    plotter.plotSphere(-10, 10, 0, 2.5, "Left Hip Joint");
    plotter.plotSphere(10, 10, 0, 2.5, "Right Hip Joint");
    
    // Legs
    plotter.plotCylinder(-10, -10, 0, 2.5, 20, "Left Leg");
    plotter.plotCylinder(10, -10, 0, 2.5, 20, "Right Leg");
    
    // Feet
    plotter.plotCuboid(-10, -30, 0, 10, 5, 5, "Left Foot");
    plotter.plotCuboid(10, -30, 0, 10, 5, 5, "Right Foot");
}

int main() {
    int choice;
    std::cout << "Choose a shape to plot:\n";
    std::cout << "5. Cuboid\n8. Sphere\n10.Cone\n11. Cylinder\n12. Robot";
    std::cout << "\nEnter choice: ";
    std::cin >> choice;

    switch (choice) {
        case 5: {
            double x, y, z, width, height, depth;
            std::cout << "Enter x, y, z, width, height, depth for Cuboid: ";
            std::cin >> x >> y >> z >> width >> height >> depth;
            Cuboid cuboid(x, y, z, width, height, depth);
            cuboid.draw();
            std::string inputFile = ".././geometry/scripts/cuboid.txt";
            std::string outputFile = ".././geometry/scripts/transformed.txt";
            performTransformation(inputFile, outputFile);
            Plotter::plot3D("../geometry/scripts/cuboid.txt",".././geometry/scripts/transformed.txt","Cuboid");
            break;
        }
        case 8: {
            double radius;
            std::cout << "Enter radius for Sphere: ";
            std::cin >> radius;
            Sphere sphere(radius);
            sphere.draw();
            std::string inputFile = ".././geometry/scripts/sphere.txt";
            std::string outputFile = ".././geometry/scripts/transformed.txt";
            performTransformation(inputFile, outputFile);
            Plotter::plot3D("../geometry/scripts/sphere.txt",".././geometry/scripts/transformed.txt", "Sphere");
            break;
        }
        case 10: {
            double radius, height;
            std::cout << "Enter base radius and height for Cone: ";
            std::cin >> radius >> height;
            Cone cone(radius, height);
            cone.draw();
            std::string inputFile = ".././geometry/scripts/cone.txt";
            std::string outputFile = ".././geometry/scripts/transformed.txt";
            performTransformation(inputFile, outputFile);
            Plotter::plot3D(".././geometry/scripts/cone.txt",".././geometry/scripts/transformed.txt", "Cone");
            break;
        }
        case 11:{
            double radius, height;
            std::cout << "Enter base radius and height for Cylinder: ";
            std::cin >> radius >> height;
            Cylinder cylinder(radius, height);
            cylinder.draw();
            std::string inputFile = ".././geometry/scripts/cylinder.txt";
            std::string outputFile = ".././geometry/scripts/transformed.txt";
            performTransformation(inputFile, outputFile);
            Plotter::plot3D(".././geometry/scripts/cylinder.txt",".././geometry/scripts/transformed.txt", "Cylinder");
            break;
        }
        case 12:{
            createRobot();
        }   
    }
    return 0;
}

