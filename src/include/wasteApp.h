#ifndef SRC_WASTEAPP_H
#define SRC_WASTEAPP_H

#include <vector>
#include <chrono>
#include <map>
#include <stack>

#include "user.h"
#include "spot.h"
#include "MutablePriorityQueue.h"
#include "edge.h"
#include "../lib/graphviewer.h"

using namespace std;

class WasteApp {
    vector<User> users;
    vector<Vertex> vertexes;
    map<int, Vertex*> vertexMap;
    vector<Edge> edges;
    vector<Spot> spots;
    vector<House> houses;
    vector<House> centrals;
    map<int, Vertex*> vertexesRevGraph;
    vector<Edge> edgesRevGraph;
    stack<Vertex*> vertexesRev;
    float xMin;
    float yMin;
    float xMax;
    float yMax;
    float graphScale;
    int maxComponent = 0;

public:
    WasteApp();

    vector<User> &getUsers();

    void setUsers(vector<User> &users);

    void addAdjacent(int v, int e);

    void addUser(User u);

    void addVertex(Vertex* v);

    void addEdge(Edge e);

    void addSpot(Spot s);

    void addHouse(House h);

    void addCentral(House c);

    bool hasVertex(int id);

    Vertex* getVertex (int id);

    void generateGraph(Vertex s);

    Edge getEdge (int id);

    int getXVertex(float x, float s);

    int getYVertex(float y, float s);

    float getGraphScale() const;

    void setGraphScale(float g);

    const vector<House> &getHouses() const;

    Spot closestSpot(const User &u, float q, enum type type);

    void homeCollection(const User &u, type type);

    void dijkstra(const int &vID);

    Vertex* held_karp(const User &w, vector<Vertex *> housesToCollect);

    float g(Vertex *s, Vertex *v, vector<Vertex *> &path);

    void generatePath(Vertex* next);

    void fillOrder(Vertex *v, stack<Vertex*> &stack);

    void util(Vertex *v);

    int conectividade();
};


#endif //SRC_WASTEAPP_H
