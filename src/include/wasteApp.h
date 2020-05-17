#ifndef SRC_WASTEAPP_H
#define SRC_WASTEAPP_H

#include <vector>

#include "user.h"
#include "vertex.h"
#include "edge.h"
#include "../lib/graphviewer.h"

using namespace std;

class WasteApp {
    vector<User> users;
    vector<Vertex> vertexes;
    vector<Edge> edges;

public:
    WasteApp();

    const vector<User> &getUsers() const;

    void setUsers(const vector<User> &users);

    void addVertex(Vertex v);

    void addEdge(Edge e);

    void generateGraph();
};


#endif //SRC_WASTEAPP_H
