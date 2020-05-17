#include "fileHandler.h"

void readUserData(WasteApp &wasteApp){
    string username, password, edge, distance, position;
    enum userType type;
    ifstream userFile("../data/userlogins.txt");
    while(getline(userFile, username)){
        getline(userFile, password);
        getline(userFile, edge);
        getline(userFile, distance);
        getline(userFile, position);
        if(position == "Client")
            type = CLIENT;
        else
            type = WORKER;
        wasteApp.addUser(User(username, password,stoi(edge),stof(distance),type));
    }
}

void readGraphData(WasteApp &wasteApp, string folder) {
    int n, id, x, y, v1, v2, c1, c2;
    string temp;

    string filename = folder + "/nodes.txt";
    ifstream nodes (filename);

    if(nodes.is_open()) {
        getline(nodes, temp);
        n = stoi(temp);

        for (int i = 0; i < n; i++) {
            getline(nodes, temp);
            c1 = temp.find(',', 0);
            id = stoi(temp.substr(1, c1 - 1));
            c2 = temp.find(',', c1 + 1);
            x = stoi(temp.substr(c1 + 2, c2 - c1 + 2));
            y = stoi(temp.substr(c2 + 2, temp.length() - 1));
            wasteApp.addVertex(Vertex(id, x, y));
        }
        nodes.close();
    } else {
        cout << "Couldn't open nodes file!" << endl;
    }

    filename = folder + "/edges.txt";
    ifstream edges (filename);

    if(edges.is_open()) {
        getline(edges, temp);
        n = stoi(temp);

        for(int i = 0; i < n; i++) {
            getline(edges, temp);
            c1 = temp.find(',', 0);
            v1 = stoi(temp.substr(1, c1-1));
            v2 = stoi(temp.substr(c1+2, temp.length()-1));
            if (wasteApp.hasVertex(v1) && wasteApp.hasVertex(v2)) {
                wasteApp.addEdge(Edge(1, i, v1, v2));
                wasteApp.getVertex(v1).addAdjacent(i);
                wasteApp.getVertex(v2).addAdjacent(i);
            }
            else cout << "Couldn't add edge: " << v1 << " -> " << v2 << endl;
        }
        edges.close();
    } else {
        cout << "Couldn't open edges file!" << endl;
    }
}
