#include "Line.h"
#include "Rectangle.h"
#include "Cuboid.h"
#include <iostream>

int main() {
    int choice;
    std::cout << "Choose a shape to plot:\n";
    std::cout << "1. 2D Line\n2. 3D Line\n3. Rectangle\n4. Square\n5. Cuboid\n6. Cube\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1: {
            double x1, y1, x2, y2;
            std::cout << "Enter x1, y1, x2, y2 for 2D Line: ";
            std::cin >> x1 >> y1 >> x2 >> y2;
            Line line(x1, y1, x2, y2);
            line.draw();
            break;
        }
        case 2: { 
            double x1, y1, z1, x2, y2, z2;
            std::cout << "Enter x1, y1, z1, x2, y2, z2 for 3D Line: ";
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            Line line(x1, y1, z1, x2, y2, z2); 
            line.draw();
            break;
        }
        case 3: {
            double x, y, width, height;
            std::cout << "Enter x, y, width, height for Rectangle: ";
            std::cin >> x >> y >> width >> height;
            Rectangle rectangle(x, y, width, height);
            rectangle.draw();
            break;
        }
        case 4: {
            double x, y, side;
            std::cout << "Enter x, y, side length for Square: ";
            std::cin >> x >> y >> side;
            Square square(x, y, side);
            square.draw();
            break;
        }
        case 5: {
            double x, y, z, width, height, depth;
            std::cout << "Enter x, y, z, width, height, depth for Cuboid: ";
            std::cin >> x >> y >> z >> width >> height >> depth;
            Cuboid cuboid(x, y, z, width, height, depth);
            cuboid.draw();
            break;
        }
        case 6: {  
            double x, y, z, side;
            std::cout << "Enter x, y, z, side length for Cube: ";
            std::cin >> x >> y >> z >> side;
            Cuboid cube(x, y, z, side, side, side);  
            cube.draw();
            break;
        }
        default:
            std::cout << "Invalid choice!\n";
    }

    return 0;
}