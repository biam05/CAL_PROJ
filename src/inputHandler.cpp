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

int ih_request(vector<User>&users, const string &user, const string &type, const string &quantity){
    enum type tGlass = GLASS, tPaper = PAPER, tPlastic = PLASTIC, tOrganic = ORGANIC;
    for(User &u : users){
        if(u.getUsername() == user){

            vector<HouseRequest> r = u.getRequests();
            if (type == "Organic")       r.push_back(HouseRequest(tOrganic, stoi(quantity)));
            else if(type == "Glass")     r.push_back(HouseRequest(tGlass, stoi(quantity)));
            else if(type == "Paper")     r.push_back(HouseRequest(tPaper, stoi(quantity)));
            else if(type == "Plastic")   r.push_back(HouseRequest(tPlastic, stoi(quantity)));
            u.setRequests(r);

            ofstream ologinfile("../data/requests.txt",fstream::app);
            ologinfile << "\n" << user << "\n" << type << "\n" << quantity << "\n";

            return 0;
        }
    }
    return 1;
}