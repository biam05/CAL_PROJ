#include "include/gui.h"

void start_GUI(){
    gui_header();
    gui_about();
    gui_mainMenu();
}

void gui_header(){
    cout << "___       __             _____     _______                 \n"
            "__ |     / /_____ _________  /________    |_______________ \n"
            "__ | /| / /_  __ `/_  ___/  __/  _ \\_  /| |__  __ \\__  __ \\\n"
            "__ |/ |/ / / /_/ /_(__  )/ /_ /  __/  ___ |_  /_/ /_  /_/ /\n"
            "____/|__/  \\__,_/ /____/ \\__/ \\___//_/  |_|  .___/_  .___/ \n"
            "                                          /_/     /_/      " << endl;
}

void gui_about(){
    cout << "\n INSERT SHORT DESCRIPTION HERE \n";
}

void gui_mainMenu(){

    int ans = 0, ret;
    string user, password, address = "";

    cout << "\nEnter an option:\n\n";

    cout << "[1] Login\n";
    cout << "[2] Sign in\n";
    cout << "[0] Exit\n";

    cout << "\nOption: ";

    cin >> ans;
    cin.ignore(1000, '\n');

    if (system("CLS")) system("clear");

    switch(ans){
        case 1: // --- Login
            cout << "Login\n\n";
            cout << "Username:";
            getline(cin,user);
            cout << "Password:";
            getline(cin,password);
            if (system("CLS"))
                system("clear");
            ret = ih_login(user,password,address);
            if (ret == 0)
                cout << "client()";
            if (ret == 1)
                cout << "worker()";
            if (ret == 2)
                cout << "Wrong password\n";
            else
                cout << "Unknown username\n";
            break;
        case 2: // --- Sign in

            break;
        case 0: // --- Exit

            break;
        default:
            break;
    }
}