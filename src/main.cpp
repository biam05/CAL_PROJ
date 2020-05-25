#include "fileHandler.h"
#include "gui.h"
#include "wasteApp.h"

using namespace std;

int main() {
    WasteApp wasteApp;
    int ans = 0;

    gui_baseScreen();

    cout << "\t\t\tWelcome to WasteApp!\n\n";

    cout << "\n What maps do you want to use:\n\n";

    cout << " [1] 4x4 (TESTING)\n";
    cout << " [2] Porto\n";
    cout << " [0] Exit\n";

    cout << "\n Option: ";

    cin >> ans;
    cin.ignore(1000, '\n');

    // --- READING INFORMATION FROM FILES
    switch(ans){
        case 1:
            if (system("CLS")) system("clear");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t    LOADING DATA...";
            readUserData(wasteApp, "../data/GridGraphs/4x4/userlogins.txt");
            readSpotsData(wasteApp, "../data/GridGraphs/4x4/tags.txt");
            readGraphData(wasteApp, "../data/GridGraphs/4x4");
            wasteApp.setGraphScale(1);
            break;
        case 2:
            readUserData(wasteApp, "../data/Porto/userlogins.txt");
            readSpotsData(wasteApp, "../data/Porto/tags.txt");
            readGraphData(wasteApp, "../data/Porto");
            wasteApp.setGraphScale(0.1);
            break;
        default:
            return 0;

    }
    readRequestData(wasteApp);

    // --- START GUI
    start_GUI(wasteApp);

    return 0;
}