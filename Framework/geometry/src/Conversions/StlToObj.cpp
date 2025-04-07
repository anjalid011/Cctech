#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Conversions/StlToObj.h"
#include "Conversions/Triangle.h"

void convertSTLtoOBJ(const std::string& stlFilename, const std::string& objFilename) {
    std::ifstream stlFile(stlFilename);
    if (!stlFile) {
        std::cerr << "Error: Cannot open " << stlFilename << "!\n";
        return;
    }

    std::ofstream objFile(objFilename);
    if (!objFile) {
        std::cerr << "Error: Cannot create " << objFilename << "!\n";
        return;
    }

    std::string line;
    std::vector<Vec3> vertices;
    std::vector<Triangle> triangles;

    while (std::getline(stlFile, line)) {
        std::stringstream ss(line);
        std::string keyword;
        ss >> keyword;

        if (keyword == "vertex") {
            Vec3 v;
            ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);

            // Once we have 3 vertices, create a Triangle
            if (vertices.size() == 3) {
                Triangle triangle(vertices[0], vertices[1], vertices[2]);
                triangles.push_back(triangle);
                vertices.clear(); // Clear vertices for the next triangle
            }
        }
    }

    // Write to OBJ file
    int vertexIndex = 1; // OBJ vertex indices start from 1
    for (const auto& triangle : triangles) {
        // Write vertices
        objFile << "v " << triangle.v1.x << " " << triangle.v1.y << " " << triangle.v1.z << "\n";
        objFile << "v " << triangle.v2.x << " " << triangle.v2.y << " " << triangle.v2.z << "\n";
        objFile << "v " << triangle.v3.x << " " << triangle.v3.y << " " << triangle.v3.z << "\n";

        // Write face (using the vertex indices)
        objFile << "f " << vertexIndex << " " << vertexIndex + 1 << " " << vertexIndex + 2 << "\n";
        vertexIndex += 3;
    }

    stlFile.close();
    objFile.close();
    std::cout << "Conversion successful: " << objFilename << " created.\n";
}