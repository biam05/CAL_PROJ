#include "fileHandler.h"
#include "gui.h"
#include "wasteApp.h"

using namespace std;

int main() {
    WasteApp wasteApp;

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t    LOADING DATA...";

    // --- READING INFORMATION FROM FILES
    readUserData(wasteApp);
    readSpotsData(wasteApp);
    readRequestData(wasteApp);
    readGraphData(wasteApp, "../data/GridGraphs/4x4");

    // --- START GUI
    start_GUI(wasteApp);

    return 0;
}