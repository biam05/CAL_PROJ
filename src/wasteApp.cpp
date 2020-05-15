#include "wasteApp.h"

WasteApp::WasteApp() {}

const vector<User> &WasteApp::getUsers() const {
    return users;
}

void WasteApp::setUsers(const vector<User> &users) {
    WasteApp::users = users;
}



