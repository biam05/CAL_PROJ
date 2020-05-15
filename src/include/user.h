#ifndef SRC_USER_H
#define SRC_USER_H

#include "spots.h"

class User {
    enum type type;
    float quantity;
    int location_ID;
    float distance;

public:
    User(enum type t, float q, int l, float d) : type(t), quantity(q), location_ID(l), distance(d) {};

    void set_type(enum type t);
    void set_quantity(float q);

    enum type get_type();
    float get_quantity();
    int get_location_ID();
    float get_distance();
};

#endif //SRC_USER_H
