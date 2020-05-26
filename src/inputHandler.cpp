#include "include/inputHandler.h"

int ih_login(const vector<User> &users, const string &user, const string &pass)
{
    for (const auto &u : users){
        if(u.getUsername() == user){
            if(u.getPassword() == pass){
                if(u.getType() == CLIENT) return 0;              // if the user is a client
                else                      return 1;              // if the user is a worker
            }
            else
                return 2;                                        // if the user typed the wrong password
        }
    }
    return 3;                                                    // if the user isn't found
}

int ih_signin(WasteApp &wasteApp, const string &user, const string &pass, const string &vertex, char role)
{
    string username, password, position;
    vector<User> users = wasteApp.getUsers();
    enum userType type;

    for(const auto &u : users){
        if(u.getUsername() == user)         // If the user already exists
            return 1;
    }

    if(wasteApp.getGraphScale() == 1){
        // 4x4 map
        ofstream ologinfile("../data/GridGraphs/4x4/userlogins.txt",fstream::app);

        // Writes to the user file
        ologinfile << "\n" << user << "\n" << pass << "\n" << vertex << "\n";
        if (role == 'c'){
            ologinfile << "Client";
            type = CLIENT;
        }
        else{
            ologinfile << "Worker";
            type = WORKER;
        }
    }
    else {
        // Porto map
        ofstream ologinfile("../data/Porto/userlogins.txt",fstream::app);

        // Writes to the user file
        ologinfile << "\n" << user << "\n" << pass << "\n" << vertex << "\n";
        if (role == 'c'){
            ologinfile << "Client";
            type = CLIENT;
        }
        else{
            ologinfile << "Worker";
            type = WORKER;
        }
    }

    // Adds the user to the WasteApp users
    users.emplace_back(username, password, stoi(vertex), type);

    wasteApp.setUsers(users);

    return 0;
}

int ih_request(vector<User>&users, const string &user, const string &type, const string &quantity){
    enum type tGlass = GLASS, tPaper = PAPER, tPlastic = PLASTIC, tOrganic = ORGANIC;

    for(User &u : users){
        // Looks for the user that made the request
        if(u.getUsername() == user){

            vector<HouseRequest> r = u.getRequests();

            // Adds a new request to the user requests
            if (type == "Organic")       r.push_back(HouseRequest(tOrganic, stof(quantity)));
            else if(type == "Glass")     r.push_back(HouseRequest(tGlass, stof(quantity)));
            else if(type == "Paper")     r.push_back(HouseRequest(tPaper, stof(quantity)));
            else if(type == "Plastic")   r.push_back(HouseRequest(tPlastic, stof(quantity)));

            u.setRequests(r);

            ofstream ologinfile("../data/requests.txt",fstream::app);

            // Writes to the request file
            ologinfile << "\n" << user << "\n" << type << "\n" << quantity << "\n";

            return 0;
        }
    }
    return 1;
}