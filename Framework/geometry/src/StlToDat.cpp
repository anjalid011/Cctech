#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "StlToDat.h"
#include "Triangle.h"

void StlToDat::convertSTLtoDAT(const std::string& stlFilename, const std::string& datFilename) {
    std::ifstream stlFile(stlFilename);
    if (!stlFile) {
        std::cerr << "Error: Cannot open " << stlFilename << "!\n";
        return;
    }

    std::ofstream datFile(datFilename);
    if (!datFile) {
        std::cerr << "Error: Cannot create " << datFilename << "!\n";
        return;
    }

    std::string line;
    std::vector<Triangle> triangles;
    std::vector<Vec3> vertices;

    while (std::getline(stlFile, line)) {
        std::stringstream ss(line);
        std::string keyword;
        ss >> keyword;

        if (keyword == "vertex") {
            Vec3 v;
            ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
    }

    // Write to DAT file
    for (size_t i = 0; i < vertices.size(); i += 3) {
        datFile << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << "\n";
        datFile << vertices[i + 1].x << " " << vertices[i + 1].y << " " << vertices[i + 1].z << "\n";
        datFile << vertices[i + 2].x << " " << vertices[i + 2].y << " " << vertices[i + 2].z << "\n";
        datFile << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << "\n\n\n";
    }

    stlFile.close();
    datFile.close();
    std::cout << "Conversion successful: " << datFilename << " created.\n";
}