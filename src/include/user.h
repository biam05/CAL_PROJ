#ifndef SRC_USER_H
#define SRC_USER_H

#include <string>
#include <vector>
#include "house.h"
#include "houseRequest.h"

using namespace std;

enum userType {CLIENT, WORKER};

class User {
    string username;
    string password;
    House house;
    enum userType type;
    vector<HouseRequest> requests;

public:
    User(const string &username, const string &password, int vertex, userType type);

    const string &getUsername() const;
    const string &getPassword() const;
    userType getType() const;
    const House &getHouse() const;
    const vector<HouseRequest> &getRequests() const;
    void setRequests(const vector<HouseRequest> &requests);
};

#endif //SRC_USER_H
