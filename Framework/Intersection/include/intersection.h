#pragma once
#include <vector>
#include "Structure.h"

class Intersection {
public:
    // Perform boolean intersection operation on two solids
    static Shape* intersect(const Solid* solid1, const Solid* solid2);

    // Perform boolean union operation on two solids
    static Shape* unite(const Solid* solid1, const Solid* solid2);

    // Perform boolean difference operation on two solids
    static Shape* subtract(const Solid* solid1, const Solid* solid2);
};