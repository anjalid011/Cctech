#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "ObjToStl.h"

struct Vertex {
    double x, y, z;
};

struct Face {
    int v1, v2, v3; // Indices of vertices in the face
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
    std::vector<Face> faces;

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
            Face face;
            char slash; // To handle the "//" in OBJ face definitions
            iss >> face.v1 >> slash >> slash >> face.v2 >> slash >> slash >> face.v3;
            face.v1--; // Convert to 0-based index
            face.v2--;
            face.v3--;
            faces.push_back(face);
        }
    }

    // Write STL file
    stlFile << "solid obj_to_stl\n";
    for (const auto& face : faces) {
        // Compute a dummy normal (0, 0, 0) for simplicity
        stlFile << "  facet normal 0 0 0\n";
        stlFile << "    outer loop\n";
        stlFile << "      vertex " << vertices[face.v1].x << " " << vertices[face.v1].y << " " << vertices[face.v1].z << "\n";
        stlFile << "      vertex " << vertices[face.v2].x << " " << vertices[face.v2].y << " " << vertices[face.v2].z << "\n";
        stlFile << "      vertex " << vertices[face.v3].x << " " << vertices[face.v3].y << " " << vertices[face.v3].z << "\n";
        stlFile << "    endloop\n";
        stlFile << "  endfacet\n";
    }
    stlFile << "endsolid obj_to_stl\n";

    std::cout << "Conversion complete! STL file saved to\n";
}