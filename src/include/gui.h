#ifndef SRC_GUI_H
#define SRC_GUI_H

#include <iostream>
#include <stdlib.h>

#include "inputHandler.h"

using namespace std;

/** @defgroup GUI
 * @{
 *
 * GUI Functions
 */

/*! \brief Function that starts the GUI
 *
 *  Calls the main GUI functions
 */
void start_GUI();

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
 */
void gui_mainMenu();

/*! \brief Function that asks the login data that is required
 *
 *
 */
void gui_login();

/*! \brief Function that asks the sign in data that is required
 *
 *
 */
void gui_signin();

/*! \brief Function that shows the client menu
 *
 * The client menu has 3 options:
 * - ?: ???
 * - ?: ???
 * - Exit: exit program
 *
 * @param username: name of the user
 */
void gui_client(string username);

/*! \brief Function that shows the worker menu
 *
 * The worker menu has 3 options:
 * - ?: ???
 * - ?: ???
 * - Exit: exit program
 *
 * @param username: name of the user
 */
void gui_worker(string username);

/*! \brief Function that deals with an unknow user
 *
 * @return 2 if the user want to try again, 0 if the user wants to create an account
 */
int gui_unknownUser();
#endif //SRC_GUI_H
