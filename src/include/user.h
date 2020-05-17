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
    float x;
    float y;
    enum userType type;

public:
    User(const string &username, const string &password, float x, float y, userType type);

    const string &getUsername() const;
    const string &getPassword() const;
    float getX() const;
    float getY() const;
    userType getType() const;

    void setUsername(const string &username);
    void setPassword(const string &password);
    void setX(float x);
    void setY(float y);
    void setType(userType type);
};

#endif //SRC_USER_H
