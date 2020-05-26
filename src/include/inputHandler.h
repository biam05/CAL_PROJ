#ifndef SRC_INPUTHANDLER_H
#define SRC_INPUTHANDLER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "wasteApp.h"
#include "user.h"
#include "spot.h"

using namespace std;


//Function that handles the login and checks if the username and password match an existing account
int ih_login(const vector<User> &users, const string &user, const string &pass);

//Function that handles the sign in and creates an account for a new user
int ih_signin(WasteApp &wasteApp, const string &user, const string &pass, const string &vertex, char role);

//Function that handles a new request and writes it in the request file
int ih_request(vector<User>&users, const string &user, const string &type, const string &quantity);

#endif //SRC_INPUTHANDLER_H
