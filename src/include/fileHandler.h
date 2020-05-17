#ifndef SRC_FILEHANDLER_H
#define SRC_FILEHANDLER_H

#include <string>
#include <fstream>
#include <vector>

#include "user.h"
#include "wasteApp.h"

using namespace std;

/** @defgroup FileHandler
 * @{
 *
 * Input Handlers
 */

/*! \brief Function reads the data from the users
 *
 *  Saves all the information from the users
 *  @param
 */
void readUserData(WasteApp &wasteApp);

/** \brief Function reads the data from map files and generates the graph
 *
 * Saves all the information about vertexes
 * @param wasteApp the app instance
 * @param folder the folder with the graph files
 */
 void readGraphData(WasteApp &wasteApp, string folder);

#endif //SRC_FILEHANDLER_H
