#ifndef SRC_GUI_H
#define SRC_GUI_H

#include <iostream>
#include "inputHandler.h"
#include <vector>
#include "user.h"

using namespace std;

/** @defgroup GUI
 * @{
 *
 * GUI Functions
 */

/*! \brief Function that starts the GUI
 *
 *  Calls the main GUI functions
 *
 *  @param users: vector with all the WasteApp users
 */
void start_GUI(vector<User> &users);

/*! \brief Function that displays the header
 */
void gui_header();

/*! \brief Function that displays the description of the application
 *
 *
 *
 */
void gui_about();

/*! \brief Function that cleans the screen and displays the header
 */
void gui_baseScreen();

/*! \brief Function that displays the main menu
 *
 * The main menu has 3 options:
 * - Login: user login (user already has an account)
 * - Sign in: user creates an account
 * - Exit: exit program
 *
 * @param users: vector with all the WasteApp users
 */
void gui_mainMenu(vector<User> &users);

/*! \brief Function that asks the login data that is required
 *
 * @param users: vector with all the WasteApp users
 */
void gui_login(vector<User> &users);

/*! \brief Function that asks the sign in data that is required
 *
 * @param users: vector with all the WasteApp users
 */
void gui_signin(vector<User> &users);

/*! \brief Function that shows the client menu
 *
 * The client menu has 3 options:
 * - ?: ???
 * - ?: ???
 * - Exit: exit program
 *
 * @param users: vector with all the WasteApp users
 * @param username: name of the user
 */
void gui_client(vector<User> &users, const string &username);

/*! \brief Function that shows the worker menu
 *
 * Thconst e work&er menu has 3 options:
 * - ?: ???
 * - ?: ???
 * - Exit: exit program
 *
 * @param users: vector with all the WasteApp users
 * @param username: name of the user
 */
void gui_worker(vector<User> &users, const string &username);

/*! \brief Function that deals with an unknow user
 *
 * @param users: vector with all the WasteApp users
 *
 * @return 2 if the user want to try again, 0 if the user wants to create an account
 */
int gui_unknownUser(vector<User> &users);
#endif //SRC_GUI_H
