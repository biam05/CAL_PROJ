#include "wasteApp.h"

WasteApp::WasteApp() {}

const vector<User> &WasteApp::getUsers() const {
    return users;
}

void WasteApp::setUsers(const vector<User> &users) {
    WasteApp::users = users;
}

void WasteApp::addVertex(Vertex v) {
    vertexes.push_back(v);
}

void WasteApp::generateGraph() {
    GraphViewer *gv = new GraphViewer(700, 700, false);
    gv->createWindow(700, 700);
    int id, x, y;
    for(auto i = vertexes.begin(); i != vertexes.end(); i++) {
        id = i->getID();
        x = i->getX();
        y = i->getY();
        gv->addNode(id, x, y);
    }
    gv->rearrange();
}



