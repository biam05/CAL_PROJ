#include "wasteApp.h"

WasteApp::WasteApp() {
    xMin = -1;
    xMax = -1;
    yMin = -1;
    yMax = -1;
}

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
    if (v.getX() < xMin || xMin == -1) xMin = v.getX();
    if (v.getX() > xMax || xMax == -1) xMax = v.getX();
    if (v.getY() < yMin || yMin == -1) yMin = v.getY();
    if (v.getY() > yMax || yMax == -1) yMax = v.getY();

    vertexes.push_back(v);
}

void WasteApp::addEdge(Edge e) {
    edges.push_back(e);
}

void WasteApp::generateGraph() {
    GraphViewer *gv = new GraphViewer((xMax-xMin) * 0.1, (yMax - yMin) * 0.1, false);
    gv->createWindow((xMax-xMin) * 0.1, (yMax - yMin) * 0.1);

    gv->defineEdgeCurved(false);
    gv->defineVertexColor("black");

    int id, x, y;

    for(auto & vertex : vertexes) {
        id = vertex.getID();
        x = getXVertex(vertex.getX());
        y = getYVertex(vertex.getY());
        gv->addNode(id, x, y);
        gv->setVertexSize(id, 1);
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

int WasteApp::getXVertex(float x) {
    return (x - xMin) * 0.1;
}

int WasteApp::getYVertex(float y) {
    return (y - yMin) * 0.1;
}



