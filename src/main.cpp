#include "fileHandler.h"
#include "gui.h"
#include "wasteApp.h"

using namespace std;

int main() {
    WasteApp wasteApp;

    cout << "\n\n\n\n\n\n\n\t\t\tLOADING GRAPH...";

    // --- READING INFORMATION FROM FILES
    readUserData(wasteApp);
    readSpotsData(wasteApp);
    readRequestData(wasteApp);
    readGraphData(wasteApp, "../data/Porto");

    // --- START GUI
    start_GUI(wasteApp);

    return 0;
}