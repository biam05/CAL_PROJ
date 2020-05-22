#include "include/gui.h"

void start_GUI(WasteApp &wasteApp){
    gui_baseScreen();
    gui_about();
    gui_mainMenu(wasteApp);
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

void gui_mainMenu(WasteApp &wasteApp) {
    int ans = 0;
    cout << "\n Enter an option:\n\n";

    cout << " [1] Login\n";
    cout << " [2] Sign in\n";
    cout << " [0] Exit\n";

    cout << "\n Option: ";

    cin >> ans;
    cin.ignore(1000, '\n');

    gui_baseScreen();

    switch(ans) {
        case 1: // --- Login
            gui_login(wasteApp);
            break;
        case 2: // --- Sign in
            gui_signin(wasteApp);
            break;
        case 0: // --- Exit
            cout << "Goodbye!";
            break;
        default:
            break;
    }
}

void gui_login(WasteApp &wasteApp){

    int ret = 2;
    string user, password, address;

    while (ret == 2)
    {
        cout << "\t\t\tLogin\n\n";

        cout << " Username: ";
        getline(cin,user);

        cout << " Password: ";
        getline(cin,password);

        gui_baseScreen();

        switch(ret = ih_login(wasteApp.getUsers(), user,password)){
            case 0: // --- The user is a client
                gui_client(wasteApp, user);
                break;
            case 1: // --- The user is a "worker"
                gui_worker(wasteApp, user);
                break;
            case 2: // --- The user exists, but the password is wrong
                cout << " Wrong password!\n ";
                break;
            default: // --- The user doesn't exist
                ret = gui_unknownUser(wasteApp);
                break;
        }
    }
}

void gui_signin(WasteApp &wasteApp)
{
    char opt;
    string user, password, password2, vertex;

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

    cout << " Vertex: ";
    getline(cin, vertex);

    cout << " Do you intend to be a client or a worker (c/w)? ";
    cin >> opt;

    ih_signin(wasteApp.getUsers(),user,password,vertex,opt);

    if(opt =='c')
        gui_client(wasteApp, user);
    else
        gui_worker(wasteApp, user);

}

int gui_unknownUser(WasteApp &wasteApp){
    char opt;
    int ret = 0;
    cout << " Unknown username!\n Would you like to create an account? (Y/N)\n ";
    cin >> opt;
    cin.ignore(1000, '\n');
    switch(opt)
    {
        case 'Y':
        case 'y':
        {
            gui_signin(wasteApp);
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

void gui_client(WasteApp &wasteApp, const string &username){

    User user("","",-1,CLIENT);
    int ans;

    for (User &u : wasteApp.getUsers())
    {
        if (u.getUsername() == username)
            user = u;
    }
    while (true) {
        gui_baseScreen();

        cout << "\t\t\tClient Menu\n ";
        cout << endl << " Welcome, " << username << "!" << endl;

        cout << "\n Enter an option:\n\n";

        cout << " [1] Find Your Nearest Waste Deposit Spot\n";
        cout << " [2] Request Home Collection\n";
        cout << " [0] Exit\n";

        cout << "\n Option: ";

        cin >> ans;
        cin.ignore(1000, '\n');

        switch (ans) {
            case 1: // Apply Dijkstra's Algorithm to find the shortest path to the desired waste deposit spot
                gui_nearestSpot(wasteApp, user);
                //wasteApp.generateGraph();
                break;
            case 2: // Request a worker to collect a certain type of waste to your home
                gui_homeCollection(wasteApp, username);
                break;
            case 0: // Exit
                cout << "\t\t\tGoodbye!";
                return;
            default:
                break;
        }
    }
}

void gui_nearestSpot(WasteApp &wasteApp, User &user){

    string type, quantity;
    enum type wtype;
    Spot s(ORGANIC,0,0,-1);

    gui_baseScreen();

    cout << "\t\tClient Menu - Nearest Spot\n ";

    cout << endl << " What type of waste are you looking for? (Glass, Plastic, Paper, Organic) ";
    getline(cin, type);

    if (type == "Glass" || type == "glass")             wtype = GLASS;
    else if (type == "Plastic" || type == "plastic")    wtype = PLASTIC;
    else if (type == "Paper" || type == "paper")        wtype = PAPER;
    else                                                wtype = ORGANIC;

    cout << " What is the amount of waste you want to deposit? ";
    getline(cin, quantity);

    s = wasteApp.closestSpot(user,stof(quantity),wtype);

	if (s.getVertex() == -1)
	{
		cout << " Not found\n";
		// To avoid going back to the menu, waits here for an input!
		cin >> quantity;
	}
	else
	{
		cout << endl << " " << s.getVertex();
		wasteApp.generateGraph(s);
	}
}

void gui_homeCollection(WasteApp &wasteApp, const string &username){

    string type, quantity;

    gui_baseScreen();

    cout << "\t\tClient Menu - Home Collection\n ";

    cout << endl << " What type of waste you want to have collected at your house? (Glass, Plastic, Paper, Organic) ";
    getline(cin, type);

    cout << " What is the amount of waste you want to have collected? ";
    getline(cin, quantity);

    ih_request(wasteApp.getUsers(), username, type, quantity);

    cout << " Request Complete!";
}

void gui_worker(WasteApp &wasteApp, const string &username){
    int ans;

    while (true) {
        gui_baseScreen();

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

        switch (ans) {
            case 1: // --- ?
                cout << "\t\t\tOption 1!";
                break;
            case 2: // --- ?
                cout << "\t\t\tOption 2!";
                break;
            case 0: // --- Exit
                cout << "\t\t\tGoodbye!";
                return;
            default:
                break;
        }
    }
}
