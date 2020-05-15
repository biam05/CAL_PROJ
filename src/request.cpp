#include "request.h"

Request::Request(enum type type, float quantity, User *user) : type(type), quantity(quantity), user(user) {}

enum type Request::getType() const {
    return type;
}

void Request::setType(enum type type) {
    Request::type = type;
}

float Request::getQuantity() const {
    return quantity;
}

void Request::setQuantity(float quantity) {
    Request::quantity = quantity;
}

User *Request::getUser() const {
    return user;
}

void Request::setUser(User *user) {
    Request::user = user;
}
