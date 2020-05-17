#include <vector>

#include "fileHandler.h"
#include "gui.h"
#include "wasteApp.h"

int main() {
    string a;
    WasteApp wasteApp;
    readGraphData(wasteApp, "../data/GridGraphs/4x4");
    wasteApp.generateGraph();
//    readUserData(wasteApp);
//    start_GUI();
    cin >> a;
    return 0;
}