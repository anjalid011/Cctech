#include "C:\Users\Anjali Dongare\Desktop\Project\Cctech\Framework\Extrusion\include\Structure.h"

Vertex::Vertex(float x, float y, float z) : x(x), y(y), z(z) {}

Edge::Edge(Vertex* v1, Vertex* v2) : v1(v1), v2(v2) {}

Face::Face(const std::vector<Edge*>& edges) : edges(edges) {}
