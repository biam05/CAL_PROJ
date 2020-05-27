#include "user.h"

User::User(const string &username, const string &password, int vertex, userType type): username(username),
                                                                        password(password), house(vertex), type(type) {}

const string &User::getUsername() const {
    return username;
}

const string &User::getPassword() const {
    return password;
}
userType User::getType() const {
    return type;
}

const House &User::getHouse() const {
    return house;
}

const vector<HouseRequest> &User::getRequests() const {
    return requests;
}

void User::setRequests(const vector<HouseRequest> &requests) {
    User::requests = requests;
}
