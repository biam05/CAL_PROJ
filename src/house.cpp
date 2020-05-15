#include "house.h"

void House::setQuantity(float q) {
    quantity = q;
}

enum type House::getType() {
    return type;
}

float House::getQuantity() {
    return quantity;
}

int House::getEdge() {
    return edge;
}

float House::getDistance() {
    return distance;
}
