#include "houseRequest.h"

HouseRequest::HouseRequest(enum type type, float quantity) : type(type), quantity(quantity) {}

enum type HouseRequest::getType() const {
    return type;
}

float HouseRequest::getQuantity() const {
    return quantity;
}
