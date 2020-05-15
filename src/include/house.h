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

    void set_quantity(float q);

    enum type get_type();

    float get_quantity();

    int get_edge();

    float get_distance();
};
#endif //SRC_HOUSES_H
