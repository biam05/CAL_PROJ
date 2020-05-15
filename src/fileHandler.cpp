#include "fileHandler.h"

void readUserData(WasteApp &wasteApp){
    string username, password, userType, address; // --- ALTERAR: ADDRESS -> COORDENADAS
    ifstream userFile("../data/userlogins.txt");
    while(getline(userFile, username)){
        getline(userFile, password);
        getline(userFile, address);
        getline(userFile, address);
    }
}