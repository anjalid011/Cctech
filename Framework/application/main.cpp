#include "Geometry.h"
// #include <iostream>

// int main() {
//     int choice;
//     std::cout << "Choose a shape to plot:\n";
//     std::cout << "1. 2D Line\n2. 3D Line\n3. Rectangle\n4. Square\n5. Cuboid\n6. Cube\n7. Circle\n8. Sphere\n9. Triangle\n10.Cone\n";
//     std::cout << "\nEnter choice: ";
//     std::cin >> choice;

//     switch (choice) {
//         case 1: {
//             double x1, y1, x2, y2;
//             std::cout << "Enter x1, y1, x2, y2 for 2D Line: ";
//             std::cin >> x1 >> y1 >> x2 >> y2;
//             Line line(x1, y1, x2, y2);
//             line.draw();
//             break;
//         }
//         case 2: { 
//             double x1, y1, z1, x2, y2, z2;
//             std::cout << "Enter x1, y1, z1, x2, y2, z2 for 3D Line: ";
//             std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
//             Line line(x1, y1, z1, x2, y2, z2); 
//             line.draw();
//             break;
//         }
//         case 3: {
//             double x, y, width, height;
//             std::cout << "Enter x, y, width, height for Rectangle: ";
//             std::cin >> x >> y >> width >> height;
//             Rectangle rectangle(x, y, width, height);
//             rectangle.draw();
//             break;
//         }
//         case 4: {
//             double x, y, side;
//             std::cout << "Enter x, y, side length for Square: ";
//             std::cin >> x >> y >> side;
//             Square square(x, y, side);
//             square.draw();
//             break;
//         }
//         case 5: {
//             double x, y, z, width, height, depth;
//             std::cout << "Enter x, y, z, width, height, depth for Cuboid: ";
//             std::cin >> x >> y >> z >> width >> height >> depth;
//             Cuboid cuboid(x, y, z, width, height, depth);
//             cuboid.draw();
//             break;
//         }
//         case 6: {  
//             double x, y, z, side;
//             std::cout << "Enter x, y, z, side length for Cube: ";
//             std::cin >> x >> y >> z >> side;
//             Cuboid cube(x, y, z, side, side, side);  
//             cube.draw();
//             break;
//         }
//         case 7:{
//             double radius;
//             std::cout << "Enter radius for Circle: ";
//             std::cin >> radius;
//             Circle circle(radius);
//             circle.draw();    
//             break;       
//         }
//         case 8: {
//             double radius;
//             std::cout << "Enter radius for Sphere: ";
//             std::cin >> radius;
//             Sphere sphere(radius);
//             sphere.draw();
//             break;
//         }
//         case 10: {
//             double radius, height;
//             std::cout << "Enter base radius and height for Cone: ";
//             std::cin >> radius >> height;
//             Cone cone(radius, height);
//             cone.draw();
//             break;
//         }
//         default:
//             std::cout << "Invalid choice!\n";
//     }

//     return 0;
// }
#include <iostream>
#include <fstream>
#include <string>
#include "Transformations.h"

std::string createShape(int shapeChoice) {
    std::string inputFile;

    std::ofstream file(inputFile);
    // if (!file) {
    //     std::cerr << "Error: Unable to create shape file!\n";
    //     return "";
    // }
    switch (shapeChoice) {
        case 1: inputFile = ".././geometry/scripts/points.txt"; break;
        case 2: inputFile = ".././geometry/scripts/points.txt"; break;
        case 3: inputFile = ".././geometry/scripts/rectangle.txt"; break;
        case 4: inputFile = ".././geometry/scripts/square.txt"; break;
        case 5: inputFile = ".././geometry/scripts/cuboid.txt"; break;
        case 6: inputFile = ".././geometry/scripts/cube.txt"; break;
        case 7: inputFile = ".././geometry/scripts/circle.txt"; break;
        case 8: inputFile = ".././geometry/scripts/sphere.txt"; break;
        case 9: inputFile = ".././geometry/scripts/triangle.txt"; break;
        case 10: inputFile = ".././geometry/scripts/cone.txt"; break;
        default:
            std::cout << "Invalid shape choice!\n";
            return "";
    }

    std::cout << "Enter parameters for the shape:\n";
    switch (shapeChoice) {
        case 1: { // 2D Line
            double x1, y1, x2, y2;
            std::cout << "Enter x1, y1, x2, y2: ";
            std::cin >> x1 >> y1 >> x2 >> y2;
            file << x1 << " " << y1 << "\n" << x2 << " " << y2 << "\n";
            break;
        }
        case 2: { // 3D Line
            double x1, y1, z1, x2, y2, z2;
            std::cout << "Enter x1, y1, z1, x2, y2, z2: ";
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            file << x1 << " " << y1 << " " << z1 << "\n" << x2 << " " << y2 << " " << z2 << "\n";
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
        case 7:{
            double radius;
            std::cout << "Enter radius for Circle: ";
            std::cin >> radius;
            Circle circle(radius);
            circle.draw();    
            break;       
        }
        case 8: {
            double radius;
            std::cout << "Enter radius for Sphere: ";
            std::cin >> radius;
            Sphere sphere(radius);
            sphere.draw();
            break;
        }
        case 9:{
            std::cout<<"Not Ready Yet";
        }
        case 10: {
            double radius, height;
            std::cout << "Enter base radius and height for Cone: ";
            std::cin >> radius >> height;
            Cone cone(radius, height);
            cone.draw();
            break;
        }
    }

    file.close();
    return inputFile;
}

int main() {
    int shapeChoice;
    std::cout << "Choose a shape to plot:\n";
    std::cout << "1. 2D Line\n2. 3D Line\n3. Rectangle\n4. Square\n5. Cuboid\n6. Cube\n7. Circle\n8. Sphere\n9. Triangle\n10.Cone\n";
    std::cout << "Enter choice: ";
    std::cin >> shapeChoice;

    std::string inputFile = createShape(shapeChoice);
    if (inputFile.empty()) {
        return 1; // Exit if shape creation failed
    }

    //Transformations transform(inputFile);
    std::string outputFile = ".././geometry/scripts/transformed.txt";

    // int transformChoice;
    // std::cout << "Choose a transformation:\n";
    // std::cout << "1. Translation\n2. Scaling\n3. Rotation\nEnter choice: ";
    // std::cin >> transformChoice;

    // switch (transformChoice) {
    //     case 1: { // Translation
    //         double tx, ty, tz;
    //         std::cout << "Enter translation values (tx ty tz): ";
    //         std::cin >> tx >> ty >> tz;
    //         transform.applyTranslation(tx, ty, tz, outputFile);
    //         std::cout << "Transformation applied successfully! Results saved in: " << outputFile << "\n";
    //         break;
    //     }
    //     case 2: { // Scaling
    //         double sx, sy, sz;
    //         std::cout << "Enter scaling factors (sx sy sz): ";
    //         std::cin >> sx >> sy >> sz;
    //         transform.applyScaling(sx, sy, sz, outputFile);
    //         std::cout << "Transformation applied successfully! Results saved in: " << outputFile << "\n";
    //         break;
    //     }
    //     case 3: { // Rotation
    //         double angle;
    //         char axis;
    //         std::cout << "Enter rotation angle (degrees) and axis (x/y/z): ";
    //         std::cin >> angle >> axis;
    //         transform.applyRotation(angle, axis, outputFile);
    //         std::cout << "Transformation applied successfully! Results saved in: " << outputFile << "\n";
    //         break;
    //     }
    //     default:
    //         std::cout << "Invalid transformation choice!\n";
    //         return 1;
    // }

    int choice;
    std::cout << "Choose transformation:\n";
    std::cout << "1. Translation\n2. Rotation\n3. Scaling\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    Transformations::applyTransformation(inputFile, outputFile, choice);

    return 0;
}

