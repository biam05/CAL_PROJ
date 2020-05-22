#ifndef SRC_WASTEAPP_H
#define SRC_WASTEAPP_H

#include <vector>

#include "user.h"
#include "spot.h"
#include "MutablePriorityQueue.h"
#include "edge.h"
#include "../lib/graphviewer.h"

using namespace std;

class WasteApp {
    vector<User> users;
    vector<Vertex> vertexes;
    vector<Edge> edges;
    vector<Spot> spots;
    vector<House> houses;
    vector<House> centrals;
    float xMin;
    float yMin;
    float xMax;
    float yMax;

public:
    WasteApp();

    vector<User> &getUsers();

    void setUsers(vector<User> &users);

    void addAdjacent(int v, int e);

    void addUser(User u);

    void addVertex(Vertex v);

    void addEdge(Edge e);

    void addSpot(Spot s);

    void addHouse(House h);

    void addCentral(House c);

    bool hasVertex(int id);

    Vertex getVertex (int id);

    void generateGraph();

    int getXVertex(float x, float s);

    int getYVertex(float y, float s);

    Spot closestSpot(const User &u, float q, enum type type);
};


#endif //SRC_WASTEAPP_H
