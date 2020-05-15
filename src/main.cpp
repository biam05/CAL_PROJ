#include <vector>

#include "fileHandler.h"
#include "gui.h"
#include "wasteApp.h"

int main() {
    string a;
    WasteApp wasteApp;
    readUserData(wasteApp);
    start_GUI();
    cin >> a;
    return 0;
}