#include <vector>

#include "fileHandler.h"
#include "gui.h"
#include "wasteApp.h"

int main() {
    WasteApp wasteApp;
    readGraphData(wasteApp, "../data/GridGraphs/4x4");
    wasteApp.generateGraph();
    readUserData(wasteApp);
    start_GUI();
    return 0;
}