#ifndef SRC_USER_H
#define SRC_USER_H

#include <string>

// Might include this -> spot vector
// #include "spot.h"

using namespace std;

class User {
    string username;
    string password;
    int location_ID;

public:
    User(int l, string u, string p) : location_ID(l), username(u), password(p){};

    const string &getUsername() const;
    const string &getPassword() const;
    int getLocationId() const;

    void setUsername(const string &username);
    void setPassword(const string &password);
    void setLocationId(int locationId);
};

#endif //SRC_USER_H
