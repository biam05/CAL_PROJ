#include "user.h"

void User::set_type(enum type t) {
    type = t;
}

void User::set_quantity(float q) {
    quantity = q;
}

enum type User::get_type() {
    return type;
}

float User::get_quantity() {
    return quantity;
}

int User::get_location_ID() {
    return location_ID;
}

float User::get_distance() {
    return distance;
}
