#include "user.h"

User::User(const string &username, const string &password, float x, float y, userType type) : username(username),
                                                                                              password(password), x(x),
                                                                                              y(y), type(type) {}

const string &User::getUsername() const {
    return username;
}

void User::setUsername(const string &username) {
    User::username = username;
}

const string &User::getPassword() const {
    return password;
}

void User::setPassword(const string &password) {
    User::password = password;
}

userType User::getType() const {
    return type;
}

void User::setType(userType type) {
    User::type = type;
}

float User::getX() const {
    return x;
}

void User::setX(float x) {
    User::x = x;
}

float User::getY() const {
    return y;
}

void User::setY(float y) {
    User::y = y;
}



