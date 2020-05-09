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

/*! \brief Function that displays the main menu
 *
 * The main menu has 3 options:
 * - Login: user login (user already has an account)
 * - Sign in: user creates an account
 * - Exit: exit program
 */
void gui_mainMenu();

/*! \brief Function that displays the login data that is required
 *
 *
 */
void gui_login();
#endif //SRC_GUI_H
