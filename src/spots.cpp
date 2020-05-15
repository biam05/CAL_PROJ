#include "spots.h"

void Spot::set_quantity(float q) {
    quantity = q;
}

enum type Spot::get_type() {
    return type;
}

float Spot::get_quantity() {
    return quantity;
}

float Spot::get_max_quantity() {
    return max_quantity;
}

int Spot::get_edge() {
    return edge;
}

float Spot::get_distance() {
    return distance;
}

bool Spot::fits(float q) {
    return quantity + q < max_quantity;
}
