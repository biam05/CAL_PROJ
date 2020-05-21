#include "fileHandler.h"
#include "gui.h"
#include "wasteApp.h"

using namespace std;

int main() {
    WasteApp wasteApp;

    // --- READING INFORMATION FROM FILES
    readUserData(wasteApp);
    readSpotsData(wasteApp);
    readGraphData(wasteApp, "../data/Porto");

    // --- GENERATE GRAPH
    wasteApp.generateGraph();

    // --- START GUI
    start_GUI(wasteApp);

    return 0;
}