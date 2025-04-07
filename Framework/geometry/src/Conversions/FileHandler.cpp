#include "Conversions/FileHandler.h"
#include "Conversions/Triangle.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// Helper function to read vertices from an STL file
bool FileHandler::readSTLFile(const std::string& path, std::vector<Triangle>& triangles) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Error: Could not open STL file at " << path << "\n";
        return false;
    }

    std::string line;
    std::vector<Vec3> vertices;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string keyword;
        ss >> keyword;

        if (keyword == "vertex") {
            Vec3 v;
            ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);

            // Once we have 3 vertices, create a Triangle
            if (vertices.size() == 3) {
                triangles.emplace_back(vertices[0], vertices[1], vertices[2]);
                vertices.clear();
            }
        }
    }

    file.close();
    return true;
}

// Helper function to write vertices to a DAT file
bool FileHandler::writeDATFile(const std::string& path, const std::vector<Triangle>& triangles) {
    std::ofstream file(path);
    if (!file) {
        std::cerr << "Error: Could not write to DAT file at " << path << "\n";
        return false;
    }

    for (const auto& triangle : triangles) {
        file << triangle.v1.x << " " << triangle.v1.y << " " << triangle.v1.z << "\n";
        file << triangle.v2.x << " " << triangle.v2.y << " " << triangle.v2.z << "\n";
        file << triangle.v3.x << " " << triangle.v3.y << " " << triangle.v3.z << "\n\n";
    }

    file.close();
    return true;
}

// Read OBJ file
bool FileHandler::readOBJFile(const std::string& path, std::vector<Triangle>& triangles) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Error: Cannot open OBJ file " << path << "\n";
        return false;
    }

    std::vector<Vec3> vertices;
    std::string line;

    while (std::getline(file, line)) {
        if (line.rfind("v ", 0) == 0) {
            // Parse vertex
            std::stringstream ss(line.substr(2));
            Vec3 v;
            ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        } else if (line.rfind("f ", 0) == 0) {
            // Parse face
            std::stringstream ss(line.substr(2));
            int v1, v2, v3;
            ss >> v1 >> v2 >> v3;

            // Convert 1-based indices to 0-based
            triangles.emplace_back(vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1]);
        }
    }

    file.close();
    return true;
}

// Helper function to write vertices to an OBJ file
bool FileHandler::writeOBJFile(const std::string& path, const std::vector<Triangle>& triangles) {
    std::ofstream file(path);
    if (!file) {
        std::cerr << "Error: Could not write to OBJ file at " << path << "\n";
        return false;
    }

    int vertexIndex = 1; // OBJ vertex indices start from 1
    for (const auto& triangle : triangles) {
        // Write vertices
        file << "v " << triangle.v1.x << " " << triangle.v1.y << " " << triangle.v1.z << "\n";
        file << "v " << triangle.v2.x << " " << triangle.v2.y << " " << triangle.v2.z << "\n";
        file << "v " << triangle.v3.x << " " << triangle.v3.y << " " << triangle.v3.z << "\n";

        // Write face (using the vertex indices)
        file << "f " << vertexIndex << " " << vertexIndex + 1 << " " << vertexIndex + 2 << "\n";
        vertexIndex += 3;
    }

    file.close();
    return true;
}

// Conversion: STL to DAT
bool FileHandler::convertSTLtoDAT(const std::string& stlPath, const std::string& datPath) {
    std::vector<Triangle> triangles;
    if (!readSTLFile(stlPath, triangles)) return false;
    return writeDATFile(datPath, triangles);
}

// Conversion: STL to OBJ
bool FileHandler::convertSTLtoOBJ(const std::string& stlPath, const std::string& objPath) {
    std::vector<Triangle> triangles;
    if (!readSTLFile(stlPath, triangles)) return false;
    return writeOBJFile(objPath, triangles);
}

// Conversion: OBJ to STL
bool FileHandler::convertOBJtoSTL(const std::string& objPath, const std::string& stlPath) {
    std::ifstream objFile(objPath);
    if (!objFile) {
        std::cerr << "Error: Cannot open OBJ file " << objPath << "\n";
        return false;
    }

    std::ofstream stlFile(stlPath);
    if (!stlFile) {
        std::cerr << "Error: Cannot create STL file " << stlPath << "\n";
        return false;
    }

    std::vector<Vec3> vertices;
    std::vector<Triangle> triangles;

    std::string line;
    while (std::getline(objFile, line)) {
        if (line.rfind("v ", 0) == 0) {
            std::stringstream ss(line.substr(2));
            Vec3 v;
            ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        } else if (line.rfind("f ", 0) == 0) {
            std::stringstream ss(line.substr(2));
            int v1, v2, v3;
            ss >> v1 >> v2 >> v3;

            // Convert 1-based indices to 0-based
            triangles.emplace_back(vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1]);
        }
    }

    // Write STL file
    stlFile << "solid obj_to_stl\n";
    for (const auto& triangle : triangles) {
        stlFile << "  facet normal " << triangle.normal.x << " " << triangle.normal.y << " " << triangle.normal.z << "\n";
        stlFile << "    outer loop\n";
        stlFile << "      vertex " << triangle.v1.x << " " << triangle.v1.y << " " << triangle.v1.z << "\n";
        stlFile << "      vertex " << triangle.v2.x << " " << triangle.v2.y << " " << triangle.v2.z << "\n";
        stlFile << "      vertex " << triangle.v3.x << " " << triangle.v3.y << " " << triangle.v3.z << "\n";
        stlFile << "    endloop\n";
        stlFile << "  endfacet\n";
    }
    stlFile << "endsolid obj_to_stl\n";

    objFile.close();
    stlFile.close();
    return true;
}