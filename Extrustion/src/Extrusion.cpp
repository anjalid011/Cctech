#include "Extrusion.h"

Solid* Extrusion::Extrude(Face* face, const Vertex& dir, float dist) {
    Solid* newSolid = new Solid();
    std::vector<Vertex*> newVerts;

    // Step 1: Shift vertices
    for (Edge* edge : face->edges) {
        Vertex* v = edge->v1;
        newVerts.push_back(new Vertex(v->x + dir.x * dist, v->y + dir.y * dist, v->z + dir.z * dist));
    }

    // Step 2: Top face
    std::vector<Edge*> topEdges;
    for (size_t i = 0; i < newVerts.size(); ++i) {
        topEdges.push_back(new Edge(newVerts[i], newVerts[(i+1)%newVerts.size()]));
    }
    Face* topFace = new Face(topEdges);
    newSolid->faces.push_back(topFace);

    // Step 3: Side faces
    for (size_t i = 0; i < face->edges.size(); ++i) {
        Vertex* v1 = face->edges[i]->v1;
        Vertex* v2 = face->edges[i]->v2;
        Vertex* nv1 = newVerts[i];
        Vertex* nv2 = newVerts[(i+1)%newVerts.size()];

        std::vector<Edge*> sideEdges = {
            new Edge(v1, v2),
            new Edge(v2, nv2),
            new Edge(nv2, nv1),
            new Edge(nv1, v1)
        };
        newSolid->faces.push_back(new Face(sideEdges));
    }

    newSolid->faces.push_back(face);
    return newSolid;
}
