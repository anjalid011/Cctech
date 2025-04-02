#include "Geometry.h"
#include "Transformations.h"
#include <iostream>
#include "Plotter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

std::vector<std::shared_ptr<Shape>> getShape() {
    std::vector<std::shared_ptr<Shape>> shapes;

    // Add shapes to the vector
    shapes.push_back(std::make_shared<Cuboid>());
    shapes.push_back(std::make_shared<Sphere>());
    shapes.push_back(std::make_shared<Cone>());
    shapes.push_back(std::make_shared<Cylinder>());

    return shapes;
}


void performTransformation() {
    int choice;
    std::string inputFile = ".././geometry/scripts/shape.txt";
    std::string outputFile = ".././geometry/scripts/transformed.txt";
    std::cout << "Choose a transformation:\n";
    std::cout << "1. Translation\n2. Scaling\n3. Rotation\nEnter choice: ";
    std::cin >> choice;

    Transformations transform(inputFile);

    if (choice == 1) {
        double tx, ty, tz;
        std::cout << "Enter translation (tx ty tz): ";
        std::cin >> tx >> ty >> tz;
        transform.applyTranslation(tx, ty, tz, outputFile);
    } 
    else if (choice == 2) {
        double sx, sy, sz;
        std::cout << "Enter scaling factors (sx sy sz): ";
        std::cin >> sx >> sy >> sz;
        transform.applyScaling(sx, sy, sz, outputFile);
    } 
    else if (choice == 3) {
        double angle;
        char axis;
        std::cout << "Enter rotation angle (degrees) and axis (x/y/z): ";
        std::cin >> angle >> axis;
        transform.applyRotation(angle, axis, outputFile);
    } 
    else {
        std::cout << "Invalid choice!\n";
        return;
    }

    //std::cout << "Transformation applied successfully!\n";
}

int main() {
    int choice;
    std::cout << "Choose a shape to plot:\n";
    std::cout << "1. Cuboid\n2. Sphere\n3. Cone\n4. Cylinder\n";
    std::cout << "\nEnter choice: ";
    std::cin >> choice;

    // Get the vector of shapes
    std::vector<std::shared_ptr<Shape>> shapes = getShape();

    // Adjust choice to index the vector (start from 0 for vector)
    if (choice >= 1 && choice <= 4) {
        // Access the shape by index (choice - 1)
        shapes[choice - 1]->draw();
    } else {
        std::cout << "Invalid choice!\n";
    }
    int tChoice;
    std::cout << "Do you want to Perform Transformation:\n";
    std::cout << "1. Yes\n2. No\n";
    std::cout << "\nEnter choice: ";
    std::cin >> tChoice;

    if(tChoice==1){
        performTransformation();
    }
    else{
        
    }
    return 0;
}

