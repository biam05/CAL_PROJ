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

void WasteApp::generateGraph(Vertex s) {

    GraphViewer *gv = new GraphViewer((xMax-xMin) * graphScale, (yMax - yMin) * graphScale, false);
    gv->createWindow((xMax-xMin) * graphScale, (yMax - yMin) * graphScale);

    gv->defineEdgeCurved(false);
    gv->defineVertexColor("black");

    int id, x, y;

    Vertex v;

    for(auto & vertex : vertexes) {
        id = vertex.getID();
        if (id == s.getID()) v = vertex;
        x = getXVertex(vertex.getX(), graphScale);
        y = getYVertex(vertex.getY(), graphScale);
        gv->addNode(id, x, y);
        gv->setVertexSize(id, 1);
    }
    for (auto & edge : edges) {
        gv->addEdge(edge.getID(), edge.getVi(), edge.getVf(), EdgeType::UNDIRECTED);
    }
    gv->rearrange();

    Edge e;

    gv->setVertexSize(v.getID(), 10);
    gv->setVertexColor(v.getID(), "blue");

    while(v.getPrevEdge() != -1) {
        e = getEdge(v.getPrevEdge());
        gv->setEdgeColor(e.getID(), "red");
        gv->setEdgeThickness(e.getID(), 3);
        v = getVertex(e.getVi());
    }

    gv->setVertexSize(v.getID(), 10);
    gv->setVertexColor(v.getID(), "green");

    gv->rearrange();
}

void WasteApp::generatePath(Vertex next) {

    GraphViewer *gv = new GraphViewer((xMax-xMin) * graphScale, (yMax - yMin) * graphScale, false);
    gv->createWindow((xMax-xMin) * graphScale, (yMax - yMin) * graphScale);

    gv->defineEdgeCurved(false);
    gv->defineVertexColor("black");

    int id, x, y;

    Vertex v;

    for(auto & vertex : vertexes) {
        id = vertex.getID();
        if (id == next.getID()) v = vertex;
        x = getXVertex(vertex.getX(), graphScale);
        y = getYVertex(vertex.getY(), graphScale);
        gv->addNode(id, x, y);
        gv->setVertexSize(id, 1);
    }
    for (auto & edge : edges) {
        gv->addEdge(edge.getID(), edge.getVi(), edge.getVf(), EdgeType::UNDIRECTED);
    }
    gv->rearrange();

    Edge e;

    gv->setVertexSize(next.getID(), 10);
    gv->setVertexColor(next.getID(), "blue");

    while (next.getPrevVert() != -1)
    {
        dijkstra(next.getPrevVert());
        while(next.getPrevEdge() != -1) {
            e = getEdge(next.getPrevEdge());
            gv->setEdgeColor(e.getID(), "red");
            gv->setEdgeThickness(e.getID(), 3);
            next = getVertex(e.getVi());
        }
        gv->setVertexSize(next.getID(), 10);
        gv->setVertexColor(next.getID(), "yellow");
    }

    gv->setVertexSize(next.getID(), 10);
    gv->setVertexColor(next.getID(), "green");

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

void WasteApp::dijkstra(const int &vID)
{
    MutablePriorityQueue<Vertex> mutablePriorityQueue;
    for (auto &v : vertexes) {
        if (v.getID() == vID) {
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
                                vert.setPrevEdge(e.getID());
                                mutablePriorityQueue.insert(&vert);
                            }
                        }
                    }
                }
            }
        }
    }
}

Spot WasteApp::closestSpot(const User &u, float q, enum type type) {
    dijkstra(u.getHouse().getVertex());
    float min_dist = 1000000;
    Spot sp(type,-1,-1,-1);
    for (Spot &s : spots) {
        for (Vertex &v : vertexes) {
            if (s.getVertex() == v.getID()) {
                if (s.fits(q) && s.getType() == type) {
                    if (min_dist > v.getDistance()) {
                        min_dist = v.getDistance();
                        sp = s;
                    }
                }
            }
        }
    }
    return sp;
}

void WasteApp::homeCollection(const User &w, enum type type) {
    vector<Vertex> path;
    vector<Vertex> housesToCollect;
    string a;
    for (Vertex &v : vertexes)
    {
        if (v.getID() == w.getHouse().getVertex())
        {
            housesToCollect.push_back(v);
            break;
        }
    }
    for (User &user : users)
    {
        for (HouseRequest hr : user.getRequests())
        {
            if (hr.getType() == type) {
                for (Vertex &vert : vertexes)
                    if (vert.getID() == user.getHouse().getVertex())
                    {
                        dijkstra(w.getHouse().getVertex());
                        if (vert.getDistance() != 1000000)
                        {
                            vector<HouseRequest> reqs = user.getRequests();
                            for (auto req = reqs.begin(); req != reqs.end(); req++)
                            {
                                if ((*req).getType() == type)
                                {
                                    reqs.erase(req);
                                    req--;
                                }
                            }
                            user.setRequests(reqs);
                            housesToCollect.push_back(vert);
                        }
                    }
                break;
            }
        }
    }
    if (housesToCollect.size() == 1)
    {
        cout << " No houses requested that collection!" << endl;
        cin >> a;
        return;
    }
    // UPDATE FILE REQUESTS
    Vertex next = held_karp(w,housesToCollect);
    generatePath(next);
    cin >> a;
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

Edge WasteApp::getEdge(int id) {
    for (Edge e : edges) {
        if (id == e.getID()) return e;
    }
    return Edge(1, -1, -1, -1);
}

float minimum(const vector<float> &vec)
{
    float minimum = 1000000;
    for (float f : vec)
    {
        if (f < minimum)
            minimum = f;
    }
    return minimum;
}

float WasteApp::g(Vertex &s, Vertex &v, vector<Vertex> &path)
{
    float dist;
    if (path.empty())
    {
        v.setPrevVert(path[0].getID());
        dijkstra(s.getID());
        dist = v.getDistance();
    }
    else if (path.size() == 1)
    {
        path[0].setPrevVert(s.getID());
        dijkstra(s.getID());
        dist = path[0].getDistance();
        v.setPrevVert(path[0].getID());
        dijkstra(path[0].getID());
        dist += v.getDistance();
    }
    else
    {
        vector<float> dists;
        for (int i = 0; i < path.size(); i++)
        {
            vector<Vertex> subset;
            for (int j = 0; j < path.size(); j++)
            {
                if (i != j)
                {
                    subset.push_back(path[j]);
                }
            }
            dist = g(s,path[i],subset);
            dijkstra(path[i].getID());
            dist += v.getDistance();
            dists.push_back(dist);
        }
        vector<Vertex> subset;
        dist = minimum(dists);
        for (int i = 0; i < dists.size(); i++)
        {
            if (dists[i] == dist)
            {
                for (int j = 0; j < path.size(); j++)
                {
                    if (i != j)
                    {
                        subset.push_back(path[j]);
                    }
                }
                g(s,path[i],subset);
                v.setPrevVert(path[i].getID());
                break;
            }
        }
    }
    return dist;
}

Vertex WasteApp::held_karp(const User &w, vector<Vertex> housesToCollect) {
    float distance;
    float min_dist = 1000000;
    Vertex centralV;
    int v = w.getHouse().getVertex();
    Vertex start;
    for (Vertex &s : vertexes)
    {
        if (s.getID() == v)
        {
            start = s;
            break;
        }
    }
    for (House &c : centrals) {
        for (Vertex &vert : vertexes) {
            if (c.getVertex() == vert.getID()) {
                distance = g(start,vert,housesToCollect);
                if (min_dist > distance) {
                    min_dist = distance;
                    centralV = vert;
                }
            }
        }
    }
    g(start,centralV,housesToCollect);
    return centralV;
}

float WasteApp::getGraphScale() const {
    return graphScale;
}

void WasteApp::setGraphScale(float g) {
    graphScale = g;
}

