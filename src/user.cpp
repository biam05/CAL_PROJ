#include "user.h"

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

int User::getLocationId() const {
    return location_ID;
}

void User::setLocationId(int locationId) {
    location_ID = locationId;
}
