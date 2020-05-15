#ifndef SRC_HOUSES_H
#define SRC_HOUSES_H

#include "spot.h"

class House {
    enum type type;
    float quantity;
    int edge;
    float distance;

public:
    House (enum type t, float q, int e, float d) : type(t), quantity(q), edge(e), distance(d) {};

    void setQuantity(float q);

    enum type getType();

    float getQuantity();

    int getEdge();

    float getDistance();
};
#endif //SRC_HOUSES_H
