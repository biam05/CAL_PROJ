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

    int ans = 0;

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
            gui_login();
            break;
        case 2: // --- Sign in

            break;
        case 0: // --- Exit

            break;
        default:
            break;
    }
}

void gui_login(){
    int ret;
    string user, password, address = "";

    gui_header();

    cout << "Login\n\n";

    cout << "Username:";
    getline(cin,user);

    cout << "Password:";
    getline(cin,password);

    ret = ih_login(user,password,address);

    if (system("CLS"))
        system("clear");

    switch(ret){
        case 0: // --- The user is a client
            cout << "client()";
            break;
        case 1: // --- The user is a "worker"
            cout << "worker()";
            break;
        case 2: // --- The user exists, but the password is wrong
            cout << "Wrong password\n";
            break;
        default: // --- The user doesn't exist
            cout << "Unknown username\n";
            break;
    }
}