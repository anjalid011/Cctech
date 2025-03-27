#include "Geometry.h"
#include "Transformations.h"
#include <iostream>
#include "Plotter.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Transformations.h"
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

void createRobot(Plotter& plotter) {
    // Define Reference Point (Base of Torso)
    double xRef = 0, yRef = 0, zRef = 0;

    // Create and position body parts
    Sphere head(xRef, yRef, zRef + 50, 10); // Head
    Cone hat(xRef, yRef, zRef + 60, 10, 20); // Hat
    Cylinder neck(xRef, yRef, zRef + 45, 5, 5); // Neck
    Cylinder torso(xRef, yRef, zRef + 20, 15, 40); // Torso

    // Shoulders & Arms
    Sphere leftShoulder(xRef - 15, yRef, zRef + 35, 2.5);
    Sphere rightShoulder(xRef + 15, yRef, zRef + 35, 2.5);
    Cylinder leftArm(xRef - 15, yRef, zRef + 35, 2.5, 21);
    Cylinder rightArm(xRef + 15, yRef, zRef + 35, 2.5, 21);
    Cuboid leftHand(xRef - 35, yRef, zRef + 25, 4, 5, 5);
    Cuboid rightHand(xRef + 35, yRef, zRef + 25, 4, 5, 5);

    // Hips & Legs
    Sphere leftHip(xRef - 7.5, yRef, zRef, 2.5);
    Sphere rightHip(xRef + 7.5, yRef, zRef, 2.5);
    Cylinder leftLeg(xRef - 7.5, yRef, zRef - 20, 2.5, 20);
    Cylinder rightLeg(xRef + 7.5, yRef, zRef - 20, 2.5, 20);
    Cuboid leftFoot(xRef - 10, yRef, zRef - 30, 10, 5, 5);
    Cuboid rightFoot(xRef + 10, yRef, zRef - 30, 10, 5, 5);

    // Draw all parts
    head.draw();
    hat.draw();
    neck.draw();
    torso.draw();
    leftShoulder.draw();
    rightShoulder.draw();
    leftArm.draw();
    rightArm.draw();
    leftHand.draw();
    rightHand.draw();
    leftHip.draw();
    rightHip.draw();
    leftLeg.draw();
    rightLeg.draw();
    leftFoot.draw();
    rightFoot.draw();

    std::vector<std::string> shapeFiles;

    Sphere head(0, 0, 30, 10);  // Head position
    std::string headFile = "head.txt";
    head.saveToFile("geometry/scripts/" + headFile);
    shapeFiles.push_back(headFile);

    Cone hat(0, 0, 40, 10, 20);  // Hat on top
    std::string hatFile = "hat.txt";
    hat.saveToFile("geometry/scripts/" + hatFile);
    shapeFiles.push_back(hatFile);

    Cylinder torso(0, 0, 0, 15, 40);  // Torso
    std::string torsoFile = "torso.txt";
    torso.saveToFile("geometry/scripts/" + torsoFile);
    shapeFiles.push_back(torsoFile);

    Cuboid foot1(-10, 0, -20, 10, 5, 5);  // Left foot
    std::string foot1File = "foot1.txt";
    foot1.saveToFile("geometry/scripts/" + foot1File);
    shapeFiles.push_back(foot1File);

    // Plot the humanoid figure
    plotter.plotMultipleShapes(shapeFiles, "humanoid");
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
            //Sphere sphere(radius);
            //sphere.draw();
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
            //Cone cone(radius, height);
            //cone.draw();
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
            //Cylinder cylinder(radius, height);
            //cylinder.draw();
            std::string inputFile = ".././geometry/scripts/cylinder.txt";
            std::string outputFile = ".././geometry/scripts/transformed.txt";
            performTransformation(inputFile, outputFile);
            Plotter::plot3D(".././geometry/scripts/cylinder.txt",".././geometry/scripts/transformed.txt", "Cylinder");
            break;
        }
        case 12:{
            createRobot();
            //plotMultipleShapes(const std::vector<std::string>& shapeFiles, const std::string& outputName)
        }   
    }
    return 0;
}

