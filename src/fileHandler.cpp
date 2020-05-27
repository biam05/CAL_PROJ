#include <cmath>
#include "fileHandler.h"

void readUserData(WasteApp &wasteApp, string userfilename){

    string username, password, vertex, position;
    enum userType type;

    // Open the userlogins file
    ifstream userFile(userfilename);

    // Read while the file is not empty
    while(getline(userFile, username)){
        getline(userFile, password);
        getline(userFile, vertex);
        getline(userFile, position);
        if(position == "Client")
            type = CLIENT;
        else
            type = WORKER;

        // Add the user to the WasteApp users
        wasteApp.addUser(User(username, password,stoi(vertex),type));
    }
}

void readRequestData(WasteApp &wasteapp){

    string username, type, quantity;
    auto tGlass = GLASS, tPaper = PAPER, tPlastic = PLASTIC, tOrganic = ORGANIC;

    // Open the file with the requests information
    ifstream requestFile("../data/requests.txt");

    // Read while the file is not empty
    while(getline(requestFile, username))
    {
        getline(requestFile, type);
        getline(requestFile, quantity);

        // Looks for the user that made the request found in the file
        for(User &u : wasteapp.getUsers())
        {
            if(u.getUsername() == username)
            {
                vector<HouseRequest> r = u.getRequests();
                if (type == "Organic")       r.push_back(HouseRequest(tOrganic, stoi(quantity)));
                else if(type == "Glass")     r.push_back(HouseRequest(tGlass, stoi(quantity)));
                else if(type == "Paper")     r.push_back(HouseRequest(tPaper, stoi(quantity)));
                else if(type == "Plastic")   r.push_back(HouseRequest(tPlastic, stoi(quantity)));

                // Adds the request to the vector with all the users requests
                u.setRequests(r);
            }
        }
    }
}

void readSpotsData(WasteApp &wasteApp, string spotsfilename){

    string num_tag_string, tag, num_spots_string, vertex;
    int num_tags, num_spots;
    enum type tGlass = GLASS, tPaper = PAPER, tPlastic = PLASTIC, tOrganic = ORGANIC;

    // Opens the file with all the information about the points of interest
    ifstream spotFile(spotsfilename);

    // Number of tags in the file
    getline(spotFile, num_tag_string);

    num_tags = stoi(num_tag_string);

    // While we haven't read all the tags that exist in the file
    while (num_tags != 0) {

        num_tags--;

        getline(spotFile, tag);                     // Read the tag
        getline(spotFile, num_spots_string);        // Read the number of points of interest that have that tag

        num_spots = stoi(num_spots_string);

        if (tag.substr(0, 4) == "spot") {          // If the tag corresponds to a spot
            if (tag.substr(5, 5) == "glass") {     // If the it's a spot for glass
                while (num_spots != 0) {
                    num_spots--;
                    getline(spotFile, vertex);
                    // Add the glass spot the vector that as all the spots supported by WasteApp
                    wasteApp.addSpot(Spot(tGlass,0,20,stoi(vertex)));
                }
            }
            if (tag.substr(5, 7) == "plastic") {    // If it's a spot for plastic
                while (num_spots != 0) {
                    num_spots--;
                    getline(spotFile, vertex);
                    // Add the plastic spot the vector that as all the spots supported by WasteApp
                    wasteApp.addSpot(Spot(tPlastic,0,20,stoi(vertex)));
                }
            }
            if (tag.substr(5, 5) == "paper") {      // If it's a spot for paper
                while (num_spots != 0) {
                    num_spots--;
                    getline(spotFile, vertex);
                    // Add the paper spot the vector that as all the spots supported by WasteApp
                    wasteApp.addSpot(Spot(tPaper,0,20,stoi(vertex)));
                }
            }
            if (tag.substr(5, 7) == "organic") {    // If it's a spot for organic waste
                while (num_spots != 0) {
                    num_spots--;
                    getline(spotFile, vertex);
                    // Add the organic spot the vector that as all the spots supported by WasteApp
                    wasteApp.addSpot(Spot(tOrganic,0,20,stoi(vertex)));
                }
            }
        } else if (tag.substr(0, 8) == "building") {//If the point of interest is a building
            if (tag.substr(9, 5) == "house") {      //If the building is a house
                while (num_spots != 0) {
                    num_spots--;
                    getline(spotFile, vertex);
                    // Add the house to the vector that as all the houses supported by WasteApp
                    wasteApp.addHouse(House(stoi(vertex)));
                }
            }
            if (tag.substr(9, 7) == "central") {    //If the building is a central
                while (num_spots != 0) {
                    num_spots--;
                    getline(spotFile, vertex);
                    // Add the central to the vector that as all the centrals supported by WasteApp
                    wasteApp.addCentral(House(stoi(vertex)));
                }
            }
        }
    }
}

void readGraphData(WasteApp &wasteApp, const string &folder) {
    int n, id, v1, v2, c1, c2;
    float x, y;
    string temp;

    string filename = folder + "/nodes.txt";

    // Open the file with the information about the nodes
    ifstream nodes (filename);
    if(nodes.is_open()) {

        // Get the number of all the nodes that exist in the file
        getline(nodes, temp);
        n = stoi(temp);

        for (int i = 0; i < n; i++) {
            getline(nodes, temp);
            c1 = temp.find(',', 0);
            id = stoi(temp.substr(1, c1 - 1));                  // ID of the node
            c2 = temp.find(',', c1 + 1);
            x = stof(temp.substr(c1 + 1, c2 - c1 - 1));         // X coordinate of the node
            y = stof(temp.substr(c2 + 1, temp.length() - 1));   // Y coordinate of the node
            wasteApp.addVertex(new Vertex(id, x, y));

        }
        nodes.close();
    } else {
        cout << "Couldn't open nodes file!" << endl;
    }

    filename = folder + "/edges.txt";

    // Open the file with the information about the edges
    ifstream edges (filename);

    if(edges.is_open()) {

        // Get the number of all the edges that exist in the file
        getline(edges, temp);
        n = stoi(temp);

        for(int i = 0; i < n; i++) {
            getline(edges, temp);
            c1 = temp.find(',', 0);

            v1 = stoi(temp.substr(1, c1-1));                              // Beginning vertex of the edge
            v2 = stoi(temp.substr(c1 + 1, temp.length()-1));              // Ending vertex of the edge
            if (wasteApp.hasVertex(v1) && wasteApp.hasVertex(v2)) {
                // Add an edge that has a weight calculated by the distance between the 2 vertexes
                wasteApp.addEdge(new Edge(sqrt(pow((wasteApp.getVertex(v1)->getX() - wasteApp.getVertex(v2)->getX()),2) + pow((wasteApp.getVertex(v1)->getY() - wasteApp.getVertex(v2)->getY()),2)), i, v1, v2));

                // Add the edge as one of the edges that are connected to the beginning vertex
                wasteApp.addAdjacent(v1,i);
            }
            else cout << "Couldn't add edge: " << v1 << " -> " << v2 << endl;
        }
        edges.close();
    } else {
        cout << "Couldn't open edges.txt file!" << endl;
    }
}

void updateRequests(WasteApp &wasteApp){
    string type;

    // Open the file that as all the information about the requests (to write new information)
    ofstream requestFile("../data/requests.txt");

    for(int j = 0; j < wasteApp.getUsers().size(); j++)
    {
        User u = wasteApp.getUsers()[j];

        // Get all the requests from a user
        vector<HouseRequest> r = u.getRequests();

        for(int i = 0; i < r.size(); i++)
        {
            // Check the type of waste that the user wants to have collected at his house

            if     (r[i].getType() == ORGANIC)  type = "Organic";
            else if(r[i].getType() == GLASS)    type = "Glass";
            else if(r[i].getType() == PAPER)    type = "Paper";
            else                                type = "Plastic";

            // Write to the requests file the user request
            if(i != r.size()-1 || j != wasteApp.getUsers().size())
                requestFile << u.getUsername() << endl << type << endl << r[i].getQuantity() << endl;
            else
                requestFile << endl << u.getUsername() << endl << type << endl << r[i].getQuantity();

            // Repeat for all the users
        }
    }
}
