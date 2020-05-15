#ifndef SRC_USER_H
#define SRC_USER_H

#include <string>

// Might include this -> spot vector
// #include "spot.h"

using namespace std;

enum userType {CLIENT, WORKER};

class User {
    string username;
    string password;
    pair<float, float> address;
    enum userType type;

public:
    User(const string &username, const string &password, const pair<float, float> &address, userType type);

    const string &getUsername() const;
    const string &getPassword() const;
    const pair<float, float> &getAddress() const;
    userType getType() const;

    void setUsername(const string &username);
    void setPassword(const string &password);
    void setAddress(const pair<float, float> &address);
    void setType(userType type);
};

#endif //SRC_USER_H
