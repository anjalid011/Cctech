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
    int Tchoice;
    std::cout << "Do you want to Perform Transformation:\n";
    std::cout << "1. Yes\n2. No\n";
    std::cout << "\nEnter choice: ";
    std::cin >> Tchoice;

    if(Tchoice==1){
        Transformations transform;
        std::string inputFile= ".././geometry/scripts/cone.txt";
        std::string outputFile= ".././geometry/scripts/transformed.txt";
        transform.performTransformation(inputFile, outputFile);
    }
    else{
        
    }
    return 0;
}

