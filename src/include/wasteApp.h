#ifndef SRC_WASTEAPP_H
#define SRC_WASTEAPP_H

#include <vector>

#include "user.h"

using namespace std;

class WasteApp {
    vector<User> users;

public:
    WasteApp();

    const vector<User> &getUsers() const;

    void setUsers(const vector<User> &users);

};


#endif //SRC_WASTEAPP_H
