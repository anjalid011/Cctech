#include "Conversions/FileHandler.h"
#include "Conversions/Triangle.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>

// Helper function to read vertices from an STL file
bool FileHandler::readSTLFile(const std::string& path, std::vector<Triangle>& triangles) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Error: Could not open STL file at " << path << "\n";
        return false;
    }

    std::string line;
    std::vector<Vec3> uniqueVertices;
    std::unordered_map<Vec3, int> vertexIndexMap;

    auto getVertexIndex = [&](const Vec3& v) -> int {
        if (vertexIndexMap.find(v) == vertexIndexMap.end()) {
            vertexIndexMap[v] = uniqueVertices.size();
            uniqueVertices.push_back(v);
        }
        return vertexIndexMap[v];
    };

    while (std::getline(file, line)) {
        if (line.find("vertex") != std::string::npos) {
            // Parse vertex
            std::stringstream ss(line.substr(line.find("vertex") + 7));
            Vec3 v;
            ss >> v.x >> v.y >> v.z;

            // Get or add the vertex index
            int index = getVertexIndex(v);

            // Add the vertex index to the current triangle
            if (triangles.empty() || triangles.back().v3 != -1) {
                triangles.emplace_back();
                triangles.back().v1 = index;
                triangles.back().v2 = -1;
                triangles.back().v3 = -1;
            } else if (triangles.back().v2 == -1) {
                triangles.back().v2 = index;
            } else {
                triangles.back().v3 = index;
                triangles.back().computeNormal(uniqueVertices);
            }
        }
    }

    file.close();
    return true;
}

// Helper function to write vertices to a DAT file
bool FileHandler::writeDATFile(const std::string& path, const std::vector<Vec3>& uniqueVertices, const std::vector<Triangle>& triangles) {
    std::ofstream file(path);
    if (!file) {
        std::cerr << "Error: Could not write to DAT file at " << path << "\n";
        return false;
    }

    // Write vertices
    for (const auto& vertex : uniqueVertices) {
        file << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    }

    // Write triangles
    for (const auto& triangle : triangles) {
        file << uniqueVertices[triangle.v1].x << " " << uniqueVertices[triangle.v1].y << " " << uniqueVertices[triangle.v1].z << "\n";
        file << uniqueVertices[triangle.v2].x << " " << uniqueVertices[triangle.v2].y << " " << uniqueVertices[triangle.v2].z << "\n";
        file << uniqueVertices[triangle.v3].x << " " << uniqueVertices[triangle.v3].y << " " << uniqueVertices[triangle.v3].z << "\n\n";
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
bool FileHandler::writeOBJFile(const std::string& path, const std::vector<Vec3>& uniqueVertices, const std::vector<Triangle>& triangles) {
    std::ofstream file(path);
    if (!file) {
        std::cerr << "Error: Could not write to OBJ file at " << path << "\n";
        return false;
    }

    // Write unique vertices
    for (const auto& vertex : uniqueVertices) {
        file << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    }

    // Write triangle faces
    for (const auto& triangle : triangles) {
        file << "f " << (triangle.v1 + 1) << " " << (triangle.v2 + 1) << " " << (triangle.v3 + 1) << "\n";
    }

    file.close();
    return true;
}

// Conversion: STL to DAT
bool FileHandler::convertSTLtoDAT(const std::string& stlPath, const std::string& datPath) {
    std::ifstream stlFile(stlPath);
    if (!stlFile) {
        std::cerr << "Error: Cannot open STL file " << stlPath << "\n";
        return false;
    }

    std::ofstream datFile(datPath);
    if (!datFile) {
        std::cerr << "Error: Cannot create DAT file " << datPath << "\n";
        return false;
    }

    std::vector<Vec3> uniqueVertices;
    std::unordered_map<Vec3, int> vertexIndexMap;
    std::vector<Triangle> triangles;

    std::string line;
    while (std::getline(stlFile, line)) {
        if (line.find("vertex") != std::string::npos) {
            // Parse vertex
            std::stringstream ss(line.substr(line.find("vertex") + 7));
            Vec3 v;
            ss >> v.x >> v.y >> v.z;

            // Get or add the vertex index
            int index;
            if (vertexIndexMap.find(v) == vertexIndexMap.end()) {
                index = uniqueVertices.size();
                uniqueVertices.push_back(v);
                vertexIndexMap[v] = index;
            } else {
                index = vertexIndexMap[v];
            }

            // Add the vertex index to the current triangle
            if (triangles.empty() || triangles.back().v3 != -1) {
                triangles.emplace_back();
                triangles.back().v1 = index;
                triangles.back().v2 = -1;
                triangles.back().v3 = -1;
            } else if (triangles.back().v2 == -1) {
                triangles.back().v2 = index;
            } else {
                triangles.back().v3 = index;
                triangles.back().computeNormal(uniqueVertices);
            }
        }
    }

    // Write to DAT file
    for (const auto& triangle : triangles) {
        datFile << uniqueVertices[triangle.v1].x << " " << uniqueVertices[triangle.v1].y << " " << uniqueVertices[triangle.v1].z << "\n";
        datFile << uniqueVertices[triangle.v2].x << " " << uniqueVertices[triangle.v2].y << " " << uniqueVertices[triangle.v2].z << "\n";
        datFile << uniqueVertices[triangle.v3].x << " " << uniqueVertices[triangle.v3].y << " " << uniqueVertices[triangle.v3].z << "\n\n";
    }

    stlFile.close();
    datFile.close();
    return true;
}

// Conversion: STL to OBJ
bool FileHandler::convertSTLtoOBJ(const std::string& stlPath, const std::string& objPath) {
    std::ifstream stlFile(stlPath);
    if (!stlFile) {
        std::cerr << "Error: Cannot open STL file " << stlPath << "\n";
        return false;
    }

    std::ofstream objFile(objPath);
    if (!objFile) {
        std::cerr << "Error: Cannot create OBJ file " << objPath << "\n";
        return false;
    }

    std::vector<Vec3> uniqueVertices;
    std::unordered_map<Vec3, int> vertexIndexMap;
    std::vector<Triangle> triangles;

    auto getVertexIndex = [&](const Vec3& v) -> int {
        if (vertexIndexMap.find(v) == vertexIndexMap.end()) {
            vertexIndexMap[v] = uniqueVertices.size();
            uniqueVertices.push_back(v);
        }
        return vertexIndexMap[v];
    };

    std::string line;
    while (std::getline(stlFile, line)) {
        if (line.find("vertex") != std::string::npos) {
            // Parse vertex
            std::stringstream ss(line.substr(line.find("vertex") + 7));
            Vec3 v;
            ss >> v.x >> v.y >> v.z;

            // Get or add the vertex index
            int index = getVertexIndex(v);

            // Add the vertex index to the current triangle
            if (triangles.empty() || triangles.back().v3 != -1) {
                triangles.emplace_back();
                triangles.back().v1 = index;
                triangles.back().v2 = -1;
                triangles.back().v3 = -1;
            } else if (triangles.back().v2 == -1) {
                triangles.back().v2 = index;
            } else {
                triangles.back().v3 = index;
                triangles.back().computeNormal(uniqueVertices);
            }
        }
    }

    // Write OBJ file
    for (const auto& vertex : uniqueVertices) {
        objFile << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    }
    for (const auto& triangle : triangles) {
        objFile << "f " << (triangle.v1 + 1) << " " << (triangle.v2 + 1) << " " << (triangle.v3 + 1) << "\n";
    }

    stlFile.close();
    objFile.close();
    return true;
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
            triangles.emplace_back(v1 - 1, v2 - 1, v3 - 1, vertices);
        }
    }

    // Write STL file
    stlFile << "solid obj_to_stl\n";
    for (const auto& triangle : triangles) {
        stlFile << "  facet normal " << triangle.normal.x << " " << triangle.normal.y << " " << triangle.normal.z << "\n";
        stlFile << "    outer loop\n";
        stlFile << "      vertex " << vertices[triangle.v1].x << " " << vertices[triangle.v1].y << " " << vertices[triangle.v1].z << "\n";
        stlFile << "      vertex " << vertices[triangle.v2].x << " " << vertices[triangle.v2].y << " " << vertices[triangle.v2].z << "\n";
        stlFile << "      vertex " << vertices[triangle.v3].x << " " << vertices[triangle.v3].y << " " << vertices[triangle.v3].z << "\n";
        stlFile << "    endloop\n";
        stlFile << "  endfacet\n";
    }
    stlFile << "endsolid obj_to_stl\n";

    objFile.close();
    stlFile.close();
    return true;
}