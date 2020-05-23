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
    //Se estiver a usar ficheiros x e y, scale = 0.01; com ficheiros lat e lon, scale = 10000
    float scale = 0.1;

    GraphViewer *gv = new GraphViewer((xMax-xMin) * scale, (yMax - yMin) * scale, false);
    gv->createWindow((xMax-xMin) * scale, (yMax - yMin) * scale);

    gv->defineEdgeCurved(false);
    gv->defineVertexColor("black");

    int id, x, y;

    Vertex v;

    for(auto & vertex : vertexes) {
        id = vertex.getID();
        if (id == s.getID()) v = vertex;
        x = getXVertex(vertex.getX(), scale);
        y = getYVertex(vertex.getY(), scale);
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

vector<Vertex> WasteApp::homeCollection(const User &w, enum type type) {
    vector<Vertex> path;
    vector<Vertex> housesToCollect;
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
    path = held_karp(w,housesToCollect);
    return path;
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

vector<vector<Vertex>> WasteApp::subsets(const vector<Vertex> &set)
{
    vector<vector<Vertex>> subset;
    vector<Vertex> empty;
    subset.push_back(empty);

    for (int i = 0; i < set.size(); i++)
    {
        vector<vector<Vertex>> subsetTemp = subset;

        for (int j = 0; j < subsetTemp.size(); j++)
            subsetTemp[j].push_back(set[i]);

        for (int j = 0; j < subsetTemp.size(); j++)
            subset.push_back(subsetTemp[j]);
    }
    return subset;
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

vector<Vertex> WasteApp::held_karp(const User &w, vector<Vertex> housesToCollect) {
    vector<vector<float>> distance;
    vector<Vertex> path;
    float min_dist = 1000000;
    Vertex centralV;
    int v = w.getHouse().getVertex();
    for (Vertex &s : vertexes)
    {
        if (s.getID() == v)
        {
            path.push_back(s);
            break;
        }
    }
    dijkstra(v);
    distance[0][0] = 0;
    for (int i = 1; i < housesToCollect.size(); i++)
    {
        distance[0][i] = housesToCollect[i].getDistance();
    }
    vector<vector<Vertex>> allSubsets = subsets(housesToCollect);

    for (int s = 1; s < housesToCollect.size() - 1; s++)
    {
        for (vector<Vertex> &subset : allSubsets)
        {
            if (subset.size() == s)
            {
                for (int k = 0; k < subset.size(); k++)
                {
                    vector<float> prev;
                    for (int i = 0; i < distance.size(); i++)
                    {
                        if (i != k)
                            prev.push_back(distance[s-1][i] + distance[i][k]); //??????? (╯°□°）╯︵ ┻━┻ (┬┬﹏┬┬)
                    }
                    distance[s][k] = minimum(prev);
                }
            }
        }
    }
    dijkstra(path[path.size() - 1].getID());
    for (House &c : centrals) {
        for (Vertex &vert : vertexes) {
            if (c.getVertex() == vert.getID()) {
                if (min_dist > vert.getDistance()) {
                    min_dist = vert.getDistance();
                    centralV = vert;
                }
            }
        }
    }
    path.push_back(centralV);
    return path;
}

