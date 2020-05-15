#include "user.h"

User::User(const string &username, const string &password, const pair<float, float> &address, userType type) : username(
        username), password(password), address(address), type(type) {}

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

const pair<float, float> &User::getAddress() const {
    return address;
}

void User::setAddress(const pair<float, float> &address) {
    User::address = address;
}

