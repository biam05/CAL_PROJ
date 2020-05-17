#ifndef SRC_HOUSES_H
#define SRC_HOUSES_H

#include "spot.h"

class House {
    int edge;
    float distance;

public:
    House (int e, float d) : edge(e), distance(d) {};

    int getEdge();

    float getDistance();
};
#endif //SRC_HOUSES_H
