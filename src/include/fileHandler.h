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

#endif //SRC_FILEHANDLER_H
