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

/** @defgroup InputHandler
 * @{
 *
 * Input Handlers
 */

/*! \brief Function that handles the login
 *
 *  Checks if the username and password match an existing account
 *
 *  @param users: vector with all the WasteApp users
 *  @param user: Username
 *  @param pass: Password
 *  @return The function returns 0 if the account belongs to a client, 1 if it belongs to a worker, 2 if the password is
 *  incorrect and 3 if the username isn't registered
 */
int ih_login(const vector<User> &users, const string &user, const string &pass);

/*! \brief Function that handles the sign in
 *
 *  Creates an account for a new user
 *
 *  @param users: vector with all the WasteApp users
 *  @param user: New username
 *  @param pass: New password
 *  @param vertex: Vertex of the user's house
 *  @param role: Role of the new user (either c or w)
 *  @return The function returns 0 upon success, otherwise returns another value.
 */
int ih_signin(WasteApp &wasteApp, const string &user, const string &pass, const string &vertex, char role);

int ih_request(vector<User>&users, const string &user, const string &type, const string &quantity);

#endif //SRC_INPUTHANDLER_H
