#ifndef SRC_FILEHANDLER_H
#define SRC_FILEHANDLER_H

#include <string>
#include <fstream>
#include <vector>

#include "user.h"
#include "wasteApp.h"
#include "houseRequest.h"

using namespace std;

//Function that reads the data from the users and saves all the information from them
void readUserData(WasteApp &wasteApp, string userfilename);

//Function that reads the data from the spots and saves all the information from them
void readSpotsData(WasteApp &wasteApp, string spotsfilename);

//Function that reads the date from the request's file and saves the information from them
void readRequestData(WasteApp &wasteapp);

//Function reads the data from map files and generates the graph and saves all the information about vertexes
void readGraphData(WasteApp &wasteApp, const string &folder);

//Function that updates the request file with the new information
void updateRequests(WasteApp &wasteApp);

#endif //SRC_FILEHANDLER_H
