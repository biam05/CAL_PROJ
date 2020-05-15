#ifndef SRC_REQUEST_H
#define SRC_REQUEST_H

#include <string>

#include "spot.h"
#include "user.h"

using namespace std;

class Request {

    enum type type;
    float quantity;
    User* user;

public:
    Request(enum type type, float quantity, User *user);

    enum type getType() const;
    float getQuantity() const;
    User *getUser() const;

    void setType(enum type type);
    void setQuantity(float quantity);
    void setUser(User *user);
};


#endif //SRC_REQUEST_H
