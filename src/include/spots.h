#ifndef CAL_PROJ_SPOTS_H
#define CAL_PROJ_SPOTS_H

#pragma once

#include "edges.h"

using namespace std;

enum type {PLASTIC, PAPER, GLASS, ORGANIC};

class Spot {
    enum type type;
    float quantity;
    float max_quantity;
    Edge edge;
    float distance;

public:
    Spot (enum type t, float q, float max_q, Edge e, float d) : type(t), quantity(q), max_quantity(max_q), edge(e), distance(d) {};

    void set_quantity(float q);

    enum type get_type();
    float get_quantity();
    float get_max_quantity();
    Edge get_edge();
    float get_distance();

    bool fits(float q);
};

#endif //CAL_PROJ_SPOTS_H
