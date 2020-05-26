#ifndef SRC_WASTEAPP_H
#define SRC_WASTEAPP_H

#include <vector>
#include <chrono>

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

    // USED IN KOSARAJU
    vector<Vertex> vertexesRevGraph;
    vector<Edge> edgesRevGraph;
    vector<Vertex> vertexesRev;
    int maxComponent = 0;

    // USED IN GRAPHVIEWR
    float xMin;
    float yMin;
    float xMax;
    float yMax;
    float graphScale;

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

    //Shows path from the client's house (green) to the closest spot (blue)
    void generateGraph(Vertex s);

    //Shows path from the worker's house (green) to the central (blue) passing through the houses (yellow)
    void generatePath(Vertex &next);

    Edge getEdge (int id);

    int getXVertex(float x, float s);

    int getYVertex(float y, float s);

    float getGraphScale() const;

    void setGraphScale(float g);

    const vector<House> &getHouses() const;

    //Returns the closest spot of the type provided that can fit the quantity
    Spot closestSpot(const User &u, float q, enum type type);

    //Dijkstra's algorithm beginning on vertex vID
    void dijkstra(const int &vID);

    //Generates a path that passes through the biggest number of houses possible and ends in a central
    void homeCollection(const User &u, type type);

    // Held-Karp algorithm
    Vertex held_karp(const User &w, vector<Vertex *> housesToCollect);

    // function used in Held-Karp that calculates the minimum distance and creates the correct path
    float g(Vertex &s, Vertex &v, vector<Vertex *> &path);

    // Kosaraju algorithm
    int conectividade();

    // function that marks the given vertex as visited
    void visit(Vertex &v);

    void assign(Vertex &v, Vertex &root);
};


#endif //SRC_WASTEAPP_H
