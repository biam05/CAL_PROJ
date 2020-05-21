#include "include/inputHandler.h"

int ih_login(const vector<User> &users, const string &user, const string &pass)
{
    for (const auto &u : users){
        if(u.getUsername() == user){
            if(u.getPassword() == pass){
                if(u.getType() == CLIENT)
                    return 0;
                else
                    return 1;
            }
            else
                return 2;
        }
    }
    return 3;
}

int ih_signin(vector<User> &users, const string &user, const string &pass, const string &vertex, char role)
{
    string username, password, position;
    enum userType type;
    for(const auto &u : users){
        if(u.getUsername() == user)
            return 1;
    }

    ofstream ologinfile("../data/userlogins.txt",fstream::app);
    ologinfile << "\n" << user << "\n" << pass << "\n" << vertex << "\n";
    if (role == 'c'){
        ologinfile << "Client";
        type = CLIENT;
    }
    else{
        ologinfile << "Worker";
        type = WORKER;
    }

    users.emplace_back(username, password, stoi(vertex), type);

    return 0;
}