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

//Shows path from the client's house (green) to the closest spot (blue)
void WasteApp::generateGraph(Vertex s) {
    //Create and configure the GraphViewer window
    GraphViewer *gv = new GraphViewer((xMax-xMin) * graphScale, (yMax - yMin) * graphScale, false);
    gv->createWindow((xMax-xMin) * graphScale, (yMax - yMin) * graphScale);

    gv->defineEdgeCurved(false);
    gv->defineVertexColor("black");

    int id, x, y;

    Vertex v;

    //Add vertexes to the GraphViewer graph and save Vertex s in variable v
    for(auto & vertex : vertexes) {
        id = vertex.getID();
        if (id == s.getID()) v = vertex;
        x = getXVertex(vertex.getX(), graphScale);
        y = getYVertex(vertex.getY(), graphScale);
        gv->addNode(id, x, y);
        gv->setVertexSize(id, 1);
    }
    //Add edges to the GraphViewer graph
    for (auto & edge : edges) {
        gv->addEdge(edge.getID(), edge.getVi(), edge.getVf(), EdgeType::UNDIRECTED);
    }
    gv->rearrange();

    Edge e;

    //Set the final vertex to blue
    gv->setVertexSize(v.getID(), 10);
    gv->setVertexColor(v.getID(), "blue");

    //Set the edges on the path to red
    while(v.getPrevEdge() != -1) {
        e = getEdge(v.getPrevEdge());
        gv->setEdgeColor(e.getID(), "red");
        gv->setEdgeThickness(e.getID(), 3);
        v = getVertex(e.getVi());
    }

    //Set the starting vertex to green
    gv->setVertexSize(v.getID(), 10);
    gv->setVertexColor(v.getID(), "green");

    gv->rearrange();
}

//Shows path from the worker's house (green) to the central (blue) passing through the houses (yellow)
void WasteApp::generatePath(Vertex &next) {
    //Create and configure the GraphViewer window
    GraphViewer *gv = new GraphViewer((xMax-xMin) * graphScale, (yMax - yMin) * graphScale, false);
    gv->createWindow((xMax-xMin) * graphScale, (yMax - yMin) * graphScale);

    gv->defineEdgeCurved(false);
    gv->defineVertexColor("black");

    int id, x, y;

    //Add vertexes to the GraphViewer graph
    for(auto & vertex : vertexes) {
        id = vertex.getID();
        x = getXVertex(vertex.getX(), graphScale);
        y = getYVertex(vertex.getY(), graphScale);
        gv->addNode(id, x, y);
        gv->setVertexSize(id, 1);
    }
    //Add edges to the GraphViewer graph
    for (auto & edge : edges) {
        gv->addEdge(edge.getID(), edge.getVi(), edge.getVf(), EdgeType::UNDIRECTED);
    }
    gv->rearrange();

    Edge e;

    //Set the final vertex to blue
    gv->setVertexSize(next.getID(), 10);
    gv->setVertexColor(next.getID(), "blue");

    //For each house, do Dijkstra to get the distance to get the path to the next house
    while (next.getPrevHouse() != -1)
    {
        dijkstra(next.getPrevHouse());
        for (Vertex &v : vertexes)
        {
            if (v.getID() == next.getID())
            {
                next = v;
                break;
            }
        }

        //Set the house vertex to yellow
        gv->setVertexSize(next.getPrevHouse(), 10);
        gv->setVertexColor(next.getPrevHouse(), "yellow");

        //Set the edges on the path to red
        while(next.getPrevEdge() != -1) {
            e = getEdge(next.getPrevEdge());
            gv->setEdgeColor(e.getID(), "red");
            gv->setEdgeThickness(e.getID(), 3);
            next = getVertex(e.getVi());
        }
    }

    //Set the starting vertex to green
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
    return (yMax - y) * s;
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

//Dijkstra's algorithm beginning on vertex vID
void WasteApp::dijkstra(const int &vID)
{
    MutablePriorityQueue<Vertex> mutablePriorityQueue;
    //Pre-processing: set every vertex's distance to 1000000, visited to false and prevEdge to -1 except the starting
    //vertex, whose distance is set to 0, visited to true and prevEdge to -1 and is inserted into the PriorityQueue
    for (auto &v : vertexes) {
        if (v.getID() == vID) {
            v.setVisited(true);
            v.setDistance(0);
            mutablePriorityQueue.insert(&v);
            v.setPrevEdge(-1);
        }
        else {
            v.setVisited(false);
            v.setDistance(1000000);
            v.setPrevEdge(-1);
        }
    }
    //While the mpq isn't empty, we remove the minimum element and calculate the distance (and add to the mpq if lower
    //than the previously calculated one) of each of the adjacent vertexes, setting visited to true and prevEdge to the
    //edge that led to it
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

//Returns the closest spot of the type provided that can fit the quantity
Spot WasteApp::closestSpot(const User &u, float q, enum type type) {
    //Apply Dijkstra's algorithm to set distances
    dijkstra(u.getHouse().getVertex());

    float min_dist = 1000000;
    Spot sp(type,-1,-1,-1);

    //For each vertex with a spot that can fit the quantity of the type provided, check if its distance is less than the
    //previous minimum distance)
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

    //Update the quantity on that spot
    for (Spot &s : spots) {
        if (sp.getVertex() == s.getVertex() && sp.getType() == s.getType()) {
            s.setQuantity(s.getQuantity() + q);
            break;
        }
    }
    return sp;
}

//Generates a path that passes through the biggest number of houses possible and ends in a central
void WasteApp::homeCollection(const User &w, enum type type) {
    vector<Vertex> path;
    vector<Vertex *> housesToCollect;
    string a;

    //Check for each user if they have a request for the type to be collected and their house is accessible from the
    //worker's house, in which case their house's vertex is added to the housesToCollect vector and the request is
    //deleted.
    for (User &user : users) {
        for (HouseRequest hr : user.getRequests()) {
            if (hr.getType() == type) {
                for (Vertex &vert : vertexes)
                    if (vert.getID() == user.getHouse().getVertex()) {
                        dijkstra(w.getHouse().getVertex());
                        if (vert.getDistance() != 1000000) {
                            vector<HouseRequest> reqs = user.getRequests();
                            for (auto req = reqs.begin(); req != reqs.end(); req++) {
                                if ((*req).getType() == type) {
                                    reqs.erase(req);
                                    req--;
                                }
                            }
                            user.setRequests(reqs);
                            housesToCollect.push_back(&vert);
                        }
                    }
                break;
            }
        }
    }
    if (housesToCollect.empty())
    {
        cout << " No accessible houses requested that collection!" << endl;
        cout << " Type any key to go back to your menu.";
        cin >> a;
        return;
    }

    //Apply Held-Karp algorithm to discover the minimum path that passes in all housesToCollect vertexes and generate
    //GraphViewer window
    Vertex next = held_karp(w,housesToCollect);
    generatePath(next);
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

float WasteApp::g(Vertex &s, Vertex &v, vector<Vertex *> &path)
{
    float dist;
    //If path is empty, just calculate the direct distance between s and v
    if (path.empty())
    {
        v.setPrevHouse(s.getID());
        dijkstra(s.getID());
        dist = v.getDistance();
    }
    //If path has only one house, calculate the direct distance between s and the house and sum the direct distance
    //between the house and v
    else if (path.size() == 1)
    {
        path[0]->setPrevHouse(s.getID());
        dijkstra(s.getID());
        dist = path[0]->getDistance();
        v.setPrevHouse(path[0]->getID());
        dijkstra(path[0]->getID());
        dist += v.getDistance();
    }
    //If path has two or more elements, call recursively for every subset (excluding one element at a time) and then add
    //the distance from the removed vertex and set the one with the minimum distance
    else
    {
        vector<float> dists;
        for (int i = 0; i < path.size(); i++)
        {
            vector<Vertex *> subset;
            for (int j = 0; j < path.size(); j++)
            {
                if (i != j)
                {
                    subset.push_back(path[j]);
                }
            }
            dist = g(s,*path[i],subset);
            dijkstra(path[i]->getID());
            dist += v.getDistance();
            dists.push_back(dist);
        }
        vector<Vertex *> subset;
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
                g(s,*path[i],subset);
                v.setPrevHouse(path[i]->getID());
                break;
            }
        }
    }
    return dist;
}

Vertex WasteApp::held_karp(const User &w, vector<Vertex *> housesToCollect) {
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
    //For each of the centrals, calculate the distance from the last spot of the shortest path and see if it's minimum
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
    //Recalculate the minimum path, so that the last prevHouse fields set are the shortest path ones
    g(start,centralV,housesToCollect);

    return centralV;
}

void WasteApp::setGraphScale(float g) {
    graphScale = g;
}

const vector<House> &WasteApp::getHouses() const {
    return houses;
}

float WasteApp::getGraphScale() const {
    return graphScale;
}

void WasteApp::visit(Vertex &v)
{
    if (!v.getVisited())
    {
        v.setVisited(true);
        for (int &adj : v.getAdjacentIds())
            for (Vertex &adjV : vertexes)
                if (adjV.getID() == getEdge(adj).getVf())
                    visit(adjV);
        Vertex x = v;
        x.clearAdjacentIds();
        vertexesRev.push_back(x);
    }
}

void WasteApp::assign(Vertex &v, Vertex &root)
{
    if (v.getComponent() == -1) {
        if (v.getID() == root.getID()) {
            root.setComponent(maxComponent);
            maxComponent++;
        }
        v.setComponent(root.getComponent());
        for (int &e : v.getAdjacentIds()) {
            for (Vertex &vert : vertexesRevGraph)
                if (vert.getID() == getEdge(e).getVi())
                    assign(vert,root);
        }
    }
}

int WasteApp::conectividade() {
    for (Vertex &v : vertexes)
    {
        v.setVisited(false);
    }
    for (Vertex &v : vertexes)
    {
        visit(v);
        Vertex x = v;
        x.clearAdjacentIds();
        vertexesRevGraph.push_back(x);
    }
    for (Edge &e : edges)
    {
        edgesRevGraph.push_back(Edge(e.getWeight(),e.getID(),e.getVf(),e.getVi()));
        for (Vertex &v : vertexesRevGraph)
            if (e.getVf() == v.getID())
            {
                v.addAdjacent(e.getID());
                break;
            }
    }
    while (!vertexesRev.empty())
    {
        Vertex v = vertexesRev[0];
        assign(v,v);
        vertexesRev.erase(vertexesRev.begin());
    }
    return maxComponent;
}
