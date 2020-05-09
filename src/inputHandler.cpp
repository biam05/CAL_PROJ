#include "include/inputHandler.h"

int ih_login(string user, string pass, string &address)
{
    string username, password, position;
    ifstream loginfile("data/userlogins.txt");
    while (getline(loginfile,username))
    {
        cout << "USERNAME: " << username << endl;
        cout << "USER: " << user << endl;

        if (username == user)
        {
            getline(loginfile, password);

            if (password == pass)
            {
                getline(loginfile, address);
                getline(loginfile,position);
                if (position == "Client")
                    return 0;
                if (position == "Worker")
                    return 1;
            }
            getline(loginfile, address);
            getline(loginfile,position);
            return 2;
        }
        else
        {
            getline(loginfile, password);
            getline(loginfile, address);
            getline(loginfile,position);
        }
    }
    address = "";
    return 3;
}