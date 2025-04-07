#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Conversions/ObjToStl.h"
#include "Conversions/Triangle.h" // Include the Triangle header file

struct Vertex {
    double x, y, z;
};

void ObjToStl::ConvertObjToStl() {
    std::ifstream objFile(".././geometry/scripts/shape.obj");
    if (!objFile) {
        std::cerr << "Error: Unable to open OBJ file\n";
        return;
    }

    std::ofstream stlFile(".././geometry/scripts/shape.stl");
    if (!stlFile) {
        std::cerr << "Error: Unable to open STL file\n";
        return;
    }

    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;

    std::string line;
    while (std::getline(objFile, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            // Parse vertex
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (prefix == "f") {
            // Parse face (assuming triangular faces)
            int v1, v2, v3;
            char slash; // To handle the "//" in OBJ face definitions
            iss >> v1 >> slash >> slash >> v2 >> slash >> slash >> v3;
            v1--; // Convert to 0-based index
            v2--;
            v3--;

            // Create a Triangle using the vertices
            Vec3 vertex1(vertices[v1].x, vertices[v1].y, vertices[v1].z);
            Vec3 vertex2(vertices[v2].x, vertices[v2].y, vertices[v2].z);
            Vec3 vertex3(vertices[v3].x, vertices[v3].y, vertices[v3].z);
            Triangle triangle(vertex1, vertex2, vertex3);
            triangles.push_back(triangle);
        }
    }

    // Write STL file
    stlFile << "solid obj_to_stl\n";
    for (const auto& triangle : triangles) {
        // Use the computed normal from the Triangle class
        stlFile << "  facet normal " << triangle.normal.x << " " << triangle.normal.y << " " << triangle.normal.z << "\n";
        stlFile << "    outer loop\n";
        stlFile << "      vertex " << triangle.v1.x << " " << triangle.v1.y << " " << triangle.v1.z << "\n";
        stlFile << "      vertex " << triangle.v2.x << " " << triangle.v2.y << " " << triangle.v2.z << "\n";
        stlFile << "      vertex " << triangle.v3.x << " " << triangle.v3.y << " " << triangle.v3.z << "\n";
        stlFile << "    endloop\n";
        stlFile << "  endfacet\n";
    }
    stlFile << "endsolid obj_to_stl\n";

    std::cout << "Conversion complete! STL file saved to\n";
}