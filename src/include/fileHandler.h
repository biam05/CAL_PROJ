#ifndef SRC_FILEHANDLER_H
#define SRC_FILEHANDLER_H

#include <string>
#include <fstream>

using namespace std;

/** @defgroup FileHandler
 * @{
 *
 * Input Handlers
 */

/*! \brief Function reads the data from the users
 *
 *  Saves all the information from the users
 *  @param filename: name of the file where the information is stored
 */
void readUserData(string filename);

#endif //SRC_FILEHANDLER_H
