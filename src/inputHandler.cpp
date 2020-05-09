#include "include/inputHandler.h"

int ih_login(string user, string pass, string &address)
{
    string username, password, position;
    ifstream loginfile("../data/userlogins.txt");
    while (getline(loginfile,username))
    {
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

int ih_signin(string user, string pass, string address, char role)
{
    string username, password, position;
    ifstream iloginfile("../data/userlogins.txt");
    while (getline(iloginfile,username))
    {
        if (username == user)
        {
            return 1;
        }
    }
    ofstream ologinfile("../data/userlogins.txt",fstream::app);
    ologinfile << "\n" << user << "\n" << pass << "\n" << address << "\n";
    if (role == 'c')
        ologinfile << "Client";
    else
        ologinfile << "Worker";
    return 0;
}