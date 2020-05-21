#include "user.h"

User::User(const string &username, const string &password, int edge, float distance, userType type): username(username),
                                                                password(password), house(edge, distance), type(type) {}

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

const House &User::getHouse() const {
    return house;
}
