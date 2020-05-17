#include <vector>

#include "fileHandler.h"
#include "gui.h"
#include "wasteApp.h"

using namespace std;

int main() {
    WasteApp wasteApp;

    // --- READING INFORMATION FROM FILES
    readUserData(wasteApp);
    readGraphData(wasteApp, "../data/GridGraphs/4x4");

    // --- GENERATE GRAPH
    wasteApp.generateGraph();

    // --- START GUI
    start_GUI(wasteApp.getUsers());

    return 0;
}