#ifndef SRC_USER_H
#define SRC_USER_H

#include <string>
#include "house.h"

// Might include this -> spot vector
// #include "spot.h"

using namespace std;

enum userType {CLIENT, WORKER};

class User {
    string username;
    string password;
    House house;
    enum userType type;

public:
    User(const string &username, const string &password, int edge, float distance, userType type);

    const string &getUsername() const;
    const string &getPassword() const;
    userType getType() const;
    const House &getHouse() const;

    void setUsername(const string &username);
    void setPassword(const string &password);
    void setType(userType type);
};

#endif //SRC_USER_H
