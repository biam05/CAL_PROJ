#ifndef SRC_INPUTHANDLER_H
#define SRC_INPUTHANDLER_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

/** @defgroup InputHandler
 * @{
 *
 * Input Handlers
 */

/*! \brief Function that handles the login
 *
 *  Checks if the username and password match an existing account
 *  @param user: Username
 *  @param pass: Password
 *  @param address: initially empty address, used to return the address in case the account exists
 *  @return The function returns 0 if the account belongs to a client, 1 if it belongs to a worker, 2 if the password is
 *  incorrect and 3 if the username isn't registered
 */
int ih_login(string user, string pass, string &address);

#endif //SRC_INPUTHANDLER_H
