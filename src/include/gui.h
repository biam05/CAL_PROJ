#ifndef SRC_GUI_H
#define SRC_GUI_H

#include <iostream>
#include <vector>
#include "inputHandler.h"
#include "wasteApp.h"
#include "fileHandler.h"

using namespace std;



//Function that starts the GUI and calls the main GUI functions
void start_GUI(WasteApp &wasteApp);

//Function that displays the header
void gui_header();

//Function that displays the description of the application
void gui_about();

//Function that cleans the screen and displays the header
void gui_baseScreen();

/* Function that displays the main menu
 *
 * The main menu has 3 options:
 * - Login: user login (user already has an account)
 * - Sign in: user creates an account
 * - Conectividade: study the connectivity of the map selected
 * - Exit: exit program
 */
void gui_mainMenu(WasteApp &wasteApp);

//Function that asks the login data that is required
void gui_login(WasteApp &wasteApp);

//unction that asks the sign in data that is required
void gui_signin(WasteApp &wasteApp);

/* Function that shows the client menu
 *
 * The client menu has 3 options:
 * - See the nearest spot
 * - Make a request to have the waste collected at home
 * - Exit: exit program
 */
void gui_client(WasteApp &wasteApp, const string &username);

//Function that starts the screen where the user gives the information to find the nearest waste spot
void gui_nearestSpot(WasteApp &wasteApp, User &user);

//Function that starts the screen where the user gives the information ask for someone to request waste at their house
void gui_homeCollection(WasteApp &wasteApp, const string &username);

/*Function that shows the worker menu
 *
 * The worker menu has 2 options:
 * - Request waste from houses
 * - Exit: exit program
 */
void gui_worker(WasteApp &wasteApp, const string &username);

//Function that deals with an unknown user
int gui_unknownUser(WasteApp &wasteApp);

//Function that starts the screen where the user gives the information to know which house's he has to collect waste from
void gui_collectFromHouses(WasteApp &wasteApp,  User &user);

//Function that starts the screen where the it's given information about the connectivity of the graph
void gui_conectividade(WasteApp &wasteApp);

#endif //SRC_GUI_H
