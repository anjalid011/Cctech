#pragma once
#include <vector>

struct Vertex {
    
    float x, y, z;
    Vertex(float x, float y, float z);
};

struct Edge {                          //3 * sizeof(float) = 12 bytes
    Vertex* v1;
    Vertex* v2;
    Edge(Vertex* v1, Vertex* v2);
};

struct Face {                         //24 + n * sizeof(Edge*) bytes
    std::vector<Edge*> edges;
    Face(const std::vector<Edge*>& edges);
};

struct Solid {                         //m * sizeof(Face*) bytes
    std::vector<Face*> faces;
};
