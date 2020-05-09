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

void gui_mainMenu(){

    int ans = 0;

    cout << "\n Enter an option:\n\n";

    cout << " [1] Login\n";
    cout << " [2] Sign in\n";
    cout << " [0] Exit\n";

    cout << "\n Option: ";

    cin >> ans;
    cin.ignore(1000, '\n');

    if (system("CLS")) system("clear");

    gui_header();

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
        cout << " Login\n\n";

        cout << " Username: ";
        getline(cin,user);

        cout << " Password: ";
        getline(cin,password);

        if (system("CLS"))
            system("clear");

        gui_header();
        switch(ret = ih_login(user,password,address)){
            case 0: // --- The user is a client
                cout << " Client Menu\n ";
                break;
            case 1: // --- The user is a "worker"
                cout << " Worker Menu\n ";
                break;
            case 2: // --- The user exists, but the password is wrong
                cout << " Wrong password\n ";
                break;
            default: // --- The user doesn't exist
                cout << " Unknown username\n Would you like to create an account? (Y/N)\n ";
                cin >> opt;
                cin.ignore(1000, '\n');
                switch(opt)
                {
                    case 'Y':
                    case 'y':
                    {
                        cout << " New account being created!\n";
                        gui_signin();
                        break;
                    }
                    case 'N':
                    case 'n':
                        ret = 2;
                        if (system("CLS"))
                            system("clear");
                        gui_header();
                        break;
                    default:
                        cout << " Invalid option!\n";
                }
                break;
        }
    }
}

void gui_signin()
{
    char opt;
    string user, password, password2, address;

    cout << " Sign in\n\n";

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
}