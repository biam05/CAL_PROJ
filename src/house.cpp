#include "house.h"

void House::set_quantity(float q) {
    quantity = q;
}

enum type House::get_type() {
    return type;
}

float House::get_quantity() {
    return quantity;
}

int House::get_edge() {
    return edge;
}

float House::get_distance() {
    return distance;
}
