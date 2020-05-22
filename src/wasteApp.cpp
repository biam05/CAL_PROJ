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
    //Se estiver a usar ficheiros x e y, scale = 0.01; com ficheiros lat e lon, scale = 10000
    float scale = 10000;

    GraphViewer *gv = new GraphViewer((xMax-xMin) * scale, (yMax - yMin) * scale, false);
    gv->createWindow((xMax-xMin) * scale, (yMax - yMin) * scale);

    gv->defineEdgeCurved(false);
    gv->defineVertexColor("black");

    int id, x, y;

    for(auto & vertex : vertexes) {
        id = vertex.getID();
        x = getXVertex(vertex.getX(), scale);
        y = getYVertex(vertex.getY(), scale);
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

int WasteApp::getXVertex(float x, float s) {
    return (x - xMin) * s;
}

int WasteApp::getYVertex(float y, float s) {
    return (yMax -y) * s;
}

void WasteApp::addAdjacent(int v, int e)
{
    for (Vertex &vert : vertexes)
    {
        if (vert.getID() == v)
        {
            vert.addAdjacent(e);
        }
    }
}

Spot WasteApp::closestSpot(const User &u, float q, enum type type) {
    MutablePriorityQueue<Vertex> mutablePriorityQueue;
    House house = u.getHouse();
    for (auto &v : vertexes) {
        if (v.getID() == house.getVertex()) {
            v.setVisited(true);
            v.setDistance(0);
            mutablePriorityQueue.insert(&v);
        }
        else {
            v.setVisited(false);
            v.setDistance(1000000);
        }
    }
    while (!mutablePriorityQueue.empty()) {
        Vertex v = *mutablePriorityQueue.extractMin();
        for (int &eid : v.getAdjacentIds()) {
            for (Edge &e : edges) {
                if (e.getID() == eid) {
                    for (Vertex &vert : vertexes) {
                        if (vert.getID() == e.getVf()) {
                            if (!vert.getVisited() || vert.getDistance() > v.getDistance() + e.getWeight()) {
                                vert.setDistance(v.getDistance() + e.getWeight());
                                vert.setVisited(true);
                                mutablePriorityQueue.insert(&vert);
                            }
                        }
                    }
                }
            }
        }
    }
    float min_dist = 1000000;
    Spot closestSpot(type,-1,-1,-1);
    for (Spot &s : spots) {
        for (Vertex &v : vertexes) {
            if (s.getVertex() == v.getID()) {
                if (s.fits(q) && s.getType() == type) {
                    if (min_dist > v.getDistance()) {
                        min_dist = v.getDistance();
                        closestSpot = s;
                    }
                }
            }
        }
    }
    return closestSpot;
}

void WasteApp::addSpot(Spot s) {
    spots.push_back(s);
}

void WasteApp::addHouse(House h) {
    houses.push_back(h);
}

void WasteApp::addCentral(House c) {
    centrals.push_back(c);
}

