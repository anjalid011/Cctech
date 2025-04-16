#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Triangle.h"
#include <string>
#include <vector>

struct Vertex {
    double x, y, z;
};

class FileHandler {
public:
    static bool readSTLFile(const std::string& path, std::vector<Triangle>& triangles);
    static bool writeDATFile(const std::string& path, const std::vector<Vec3>& uniqueVertices, const std::vector<Triangle>& triangles);
    static bool readOBJFile(const std::string &filePath, std::vector<Vec3> &vertices, std::vector<Triangle> &triangles);
    static bool writeOBJFile(const std::string& path, const std::vector<Vec3>& uniqueVertices, const std::vector<Triangle>& triangles);
    static bool convertSTLtoOBJ(const std::string& stlPath, const std::string& objPath);
    static bool convertSTLtoDAT(const std::string& stlPath, const std::string& datPath);
    static bool convertOBJtoSTL(const std::string& objPath, const std::string& stlPath);
};

#endif // FILEHANDLER_H
