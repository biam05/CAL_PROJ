#include "wasteApp.h"

WasteApp::WasteApp() {}

vector<User> &WasteApp::getUsers(){
    return users;
}

void WasteApp::setUsers(vector<User> &users) {
    WasteApp::users = users;
}

void WasteApp::addUser(User u) {
    users.push_back(u);
}

void WasteApp::addVertex(Vertex v) {
    vertexes.push_back(v);
}

void WasteApp::addEdge(Edge e) {
    edges.push_back(e);
}

void WasteApp::generateGraph() {
    GraphViewer *gv = new GraphViewer(700, 700, false);
    gv->createWindow(700, 700);
    int id, x, y;
    for(auto & vertex : vertexes) {
        id = vertex.getID();
        x = vertex.getX();
        y = vertex.getY();
        gv->addNode(id, x, y);
    }
    for (auto & edge : edges) {
        gv->addEdge(edge.getID(), edge.getVi(), edge.getVf(), EdgeType::UNDIRECTED);
    }
    gv->rearrange();
}

bool WasteApp::hasVertex(int id) {
    for (auto & vertex : vertexes) {
        if (vertex.getID() == id) return true;
    }
    return false;
}

Vertex WasteApp::getVertex(int id) {
    for (auto & vertex : vertexes) {
        if (vertex.getID() == id) return vertex;
    }
    return Vertex();
}



