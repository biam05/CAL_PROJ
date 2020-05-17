#include "houseRequest.h"

HouseRequest::HouseRequest(enum type type, float quantity) : type(type), quantity(quantity) {}

enum type HouseRequest::getType() const {
    return type;
}

void HouseRequest::setType(enum type type) {
    HouseRequest::type = type;
}

float HouseRequest::getQuantity() const {
    return quantity;
}

void HouseRequest::setQuantity(float quantity) {
    HouseRequest::quantity = quantity;
}
