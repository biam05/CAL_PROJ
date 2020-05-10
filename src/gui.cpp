#include "include/gui.h"

void start_GUI(){
    gui_header();
    gui_about();
    gui_mainMenu();
}

void gui_header(){
    cout << " ___       __             _____     _______                 \n"
            " __ |     / /_____ _________  /________    |_______________ \n"
            " __ | /| / /_  __ `/_  ___/  __/  _ \\_  /| |__  __ \\__  __ \\\n"
            " __ |/ |/ / / /_/ /_(__  )/ /_ /  __/  ___ |_  /_/ /_  /_/ /\n"
            " ____/|__/  \\__,_/ /____/ \\__/ \\___//_/  |_|  .___/_  .___/ \n"
            "                                           /_/     /_/      " << endl;
}

void gui_about(){
    cout << "\n INSERT SHORT DESCRIPTION HERE \n";
}

void gui_baseScreen(){
    if (system("CLS")) system("clear");
    gui_header();
}

void gui_mainMenu(){

    int ans = 0;

    cout << "\n Enter an option:\n\n";

    cout << " [1] Login\n";
    cout << " [2] Sign in\n";
    cout << " [0] Exit\n";

    cout << "\n Option: ";

    cin >> ans;
    cin.ignore(1000, '\n');

    gui_baseScreen();

    switch(ans){
        case 1: // --- Login
            gui_login();
            break;
        case 2: // --- Sign in
            gui_signin();
            break;
        case 0: // --- Exit
            cout << "Goodbye!";
            break;
        default:
            break;
    }
}

void gui_login(){

    int ret = 2;
    char opt;
    string user, password, address;

    while (ret == 2)
    {
        cout << "\t\t\tLogin\n\n";

        cout << " Username: ";
        getline(cin,user);

        cout << " Password: ";
        getline(cin,password);

        gui_baseScreen();

        switch(ret = ih_login(user,password,address)){
            case 0: // --- The user is a client
                gui_client(user);
                break;
            case 1: // --- The user is a "worker"
                gui_worker(user);
                break;
            case 2: // --- The user exists, but the password is wrong
                cout << " Wrong password!\n ";
                break;
            default: // --- The user doesn't exist
                ret = gui_unknownUser();
                break;
        }
    }
}

void gui_signin()
{
    char opt;
    string user, password, password2, address;

    gui_baseScreen();
    cout << "\t\t\tSign in\n\n";

    cout << " Username: ";
    getline(cin,user);

    cout << " Password: ";
    getline(cin,password);

    cout << " Repeat password: ";
    getline(cin,password2);

    if (password != password2) {
        cout << " The passwords don't match!\n";
        return;
    }

    cout << " Address: ";
    getline(cin, address);

    cout << " Do you intend to be a client or a worker (c/w)? ";
    cin >> opt;

    ih_signin(user,password,address,opt);

    if(opt =='c')
        gui_client(user);
    else
        gui_worker(user);

}

int gui_unknownUser(){
    char opt;
    int ret;
    cout << " Unknown username!\n Would you like to create an account? (Y/N)\n ";
    cin >> opt;
    cin.ignore(1000, '\n');
    switch(opt)
    {
        case 'Y':
        case 'y':
        {
            cout << " New account being created!\n";
            gui_signin();
            ret = 0;
            break;
        }
        case 'N':
        case 'n':
            ret = 2;
            gui_baseScreen();
            break;
        default:
            cout << " Invalid option!\n";
    }
    return ret;
}

void gui_client(string username){

    gui_baseScreen();

    int ans;

    cout << "\t\t\tClient Menu\n ";
    cout << endl << " Welcome, " << username << "!" << endl;

    cout << "\n Enter an option:\n\n";

    cout << " [1] ?\n";
    cout << " [2] ?\n";
    cout << " [0] Exit\n";

    cout << "\n Option: ";

    cin >> ans;
    cin.ignore(1000, '\n');

    gui_baseScreen();

    switch(ans){
        case 1: // --- ?
            cout << "\t\t\tOption 1!";
            break;
        case 2: // --- ?
            cout << "\t\t\tOption 2!";
            break;
        case 0: // --- Exit
            cout << "\t\t\tGoodbye!";
            break;
        default:
            break;
    }
}

void gui_worker(string username){
    gui_baseScreen();

    int ans;

    cout << "\t\t\tWorker Menu\n ";
    cout << endl << " Welcome, " << username << "!" << endl;

    cout << "\n Enter an option:\n\n";

    cout << " [1] ?\n";
    cout << " [2] ?\n";
    cout << " [0] Exit\n";

    cout << "\n Option: ";

    cin >> ans;
    cin.ignore(1000, '\n');

    gui_baseScreen();

    switch(ans){
        case 1: // --- ?
            cout << "\t\t\tOption 1!";
            break;
        case 2: // --- ?
            cout << "\t\t\tOption 2!";
            break;
        case 0: // --- Exit
            cout << "\t\t\tGoodbye!";
            break;
        default:
            break;
    }
}
