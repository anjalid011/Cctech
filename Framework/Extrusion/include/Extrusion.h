#pragma once
#include "Structure.h"

class Extrusion {
public:
    static Solid* Extrude(Face* face, const Vertex& direction, float distance);
};