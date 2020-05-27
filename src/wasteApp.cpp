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

void WasteApp::addVertex(Vertex* v) {
    if (v->getX() < xMin || xMin == -1) xMin = v->getX();
    if (v->getX() > xMax || xMax == -1) xMax = v->getX();
    if (v->getY() < yMin || yMin == -1) yMin = v->getY();
    if (v->getY() > yMax || yMax == -1) yMax = v->getY();

    vertexMap.emplace(v->getID(), v);
}

void WasteApp::addEdge(Edge* e) {
    edgeMap.emplace(e->getID(), e);
}

//Shows path from the client's house (green) to the closest spot (blue)
void WasteApp::generateGraph(Vertex s) {
    //Create and configure the GraphViewer window
    GraphViewer *gv = new GraphViewer((xMax-xMin) * graphScale + 20, (yMax - yMin) * graphScale + 20, false);
    gv->createWindow((xMax-xMin) * graphScale + 20, (yMax - yMin) * graphScale + 20);

    gv->defineEdgeCurved(false);
    gv->defineVertexColor("black");

    int id, x, y;

    Vertex* v = getVertex(s.getID());


    //Add vertexes to the GraphViewer graph
    for(auto & vertex : vertexMap) {
        id = vertex.first;
        x = getXVertex(vertex.second->getX(), graphScale);
        y = getYVertex(vertex.second->getY(), graphScale);
        gv->addNode(id, x, y);
        gv->setVertexSize(id, 1);
    }
    //Add edges to the GraphViewer graph
    for (auto & edge : edgeMap) {
        gv->addEdge(edge.second->getID(), edge.second->getVi(), edge.second->getVf(), EdgeType::UNDIRECTED);
    }
    gv->rearrange();

    Edge* e;

    //Set the final vertex to blue
    gv->setVertexSize(v->getID(), 10);
    gv->setVertexColor(v->getID(), "blue");

    //Set the edges on the path to red
    while(v->getPrevEdge() != -1) {
        e = getEdge(v->getPrevEdge());
        gv->setEdgeColor(e->getID(), "red");
        gv->setEdgeThickness(e->getID(), 3);
        v = getVertex(e->getVi());
    }

    //Set the starting vertex to green
    gv->setVertexSize(v->getID(), 10);
    gv->setVertexColor(v->getID(), "green");

    gv->rearrange();
}

//Shows path from the worker's house (green) to the central (blue) passing through the houses (yellow)
void WasteApp::generatePath(Vertex *next) {
    //Create and configure the GraphViewer window
    GraphViewer *gv = new GraphViewer((xMax-xMin) * graphScale + 20, (yMax - yMin) * graphScale + 20, false);
    gv->createWindow((xMax-xMin) * graphScale + 20, (yMax - yMin) * graphScale + 20);

    gv->defineEdgeCurved(false);
    gv->defineVertexColor("black");

    int id, x, y;

    //Add vertexes to the GraphViewer graph
    for(auto & vertex : vertexMap) {
        id = vertex.first;
        x = getXVertex(vertex.second->getX(), graphScale);
        y = getYVertex(vertex.second->getY(), graphScale);
        gv->addNode(id, x, y);
        gv->setVertexSize(id, 1);
    }
    //Add edges to the GraphViewer graph
    for (auto & edge : edgeMap) {
        gv->addEdge(edge.second->getID(), edge.second->getVi(), edge.second->getVf(), EdgeType::UNDIRECTED);
    }
    gv->rearrange();

    Edge* e;

    //Set the final vertex to blue
    gv->setVertexSize(next->getID(), 10);
    gv->setVertexColor(next->getID(), "blue");

    //For each house, do Dijkstra to get the distance to get the path to the next house
    while (next->getPrevHouse() != -1)
    {
        dijkstra(next->getPrevHouse());

        //Set the house vertex to yellow
        gv->setVertexSize(next->getPrevHouse(), 10);
        gv->setVertexColor(next->getPrevHouse(), "yellow");

        //Set the edges on the path to red
        while(next->getPrevEdge() != -1) {
            e = getEdge(next->getPrevEdge());
            gv->setEdgeColor(e->getID(), "red");
            gv->setEdgeThickness(e->getID(), 3);
            next = getVertex(e->getVi());
        }
    }

    //Set the starting vertex to green
    gv->setVertexSize(next->getID(), 10);
    gv->setVertexColor(next->getID(), "green");

    gv->rearrange();
}

bool WasteApp::hasVertex(int id) {
    return vertexMap.find(id) != vertexMap.end();
}

Vertex* WasteApp::getVertex(int id) {
    return vertexMap.at(id);
}

Vertex* WasteApp::getVertexR(int id) {
    return vertexesRevGraph.at(id);
}

Edge* WasteApp::getEdge(int id) {
    return edgeMap.at(id);
}

Edge* WasteApp::getEdgeR(int id) {
    return edgesRevGraphMap.at(id);
}

int WasteApp::getXVertex(float x, float s) {
    return (x - xMin) * s +10;
}

int WasteApp::getYVertex(float y, float s) {
    return (yMax - y) * s +10;
}

void WasteApp::addAdjacent(int v, int e)
{
    getVertex(v)->addAdjacent(e);
}

//Dijkstra's algorithm beginning on vertex vID
void WasteApp::dijkstra(const int &vID)
{
    MutablePriorityQueue<Vertex> mutablePriorityQueue;
    //Pre-processing: set every vertex's distance to 1000000, visited to false and prevEdge to -1 except the starting
    //vertex, whose distance is set to 0, visited to true and prevEdge to -1 and is inserted into the PriorityQueue
    for (auto &v : vertexMap) {
        v.second->setVisited(false);
        v.second->setDistance(1000000);
        v.second->setPrevEdge(-1);
    }

    Vertex* vI = getVertex(vID);
    vI->setVisited(true);
    vI->setDistance(0);
    vI->setPrevEdge(-1);
    mutablePriorityQueue.insert(vI);

    //While the mpq isn't empty, we remove the minimum element and calculate the distance (and add to the mpq if lower
    //than the previously calculated one) of each of the adjacent vertexes, setting visited to true and prevEdge to the
    //id of the edge that led to it
    while (!mutablePriorityQueue.empty()) {
        Vertex* v = mutablePriorityQueue.extractMin();
        for (int &eid : v->getAdjacentIds()) {
            Edge* e = getEdge(eid);
            Vertex* vf = getVertex(e->getVf());
            if (!vf->getVisited() || vf->getDistance() > (v->getDistance() + e->getWeight())) {
                    vf->setDistance(v->getDistance() + e->getWeight());
                    vf->setVisited(true);
                    vf->setPrevEdge(e->getID());
                    mutablePriorityQueue.insert(vf);
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
    //previous minimum distance
    for (Spot &s : spots) {
        Vertex* v = getVertex(s.getVertex());
        if (s.fits(q) && s.getType() == type) {
            if (min_dist > v->getDistance()) {
                min_dist = v->getDistance();
                sp = s;
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
                Vertex* v = getVertex(user.getHouse().getVertex());
                dijkstra(w.getHouse().getVertex());
                if (v->getDistance() != 1000000)
                {
                    vector<HouseRequest> reqs = user.getRequests();
                    for (auto req = reqs.begin(); req != reqs.end(); req++)
                    {
                        if (req->getType() == type)
                        {
                            reqs.erase(req);
                            req--;
                        }
                    }
                    user.setRequests(reqs);
                    housesToCollect.push_back(v);
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
    //GraphViewer window, starting with the central (last) vertex
    Vertex* central = held_karp(w, housesToCollect);
    generatePath(central);
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

float WasteApp::g(Vertex* s, Vertex* v, vector<Vertex *> &path)
{
    float dist;
    //If path is empty, just calculate the direct distance between s and v
    if (path.empty())
    {
        v->setPrevHouse(s->getID());
        dijkstra(s->getID());
        dist = v->getDistance();
    }
    //If path has only one house, calculate the direct distance between s and the house and sum the direct distance
    //between the house and v
    else if (path.size() == 1)
    {
        path[0]->setPrevHouse(s->getID());
        dijkstra(s->getID());
        dist = path[0]->getDistance();
        v->setPrevHouse(path[0]->getID());
        dijkstra(path[0]->getID());
        dist += v->getDistance();
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
            dist = g(s,path[i],subset);
            dijkstra(path[i]->getID());
            dist += v->getDistance();
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
                g(s,path[i],subset);
                v->setPrevHouse(path[i]->getID());
                break;
            }
        }
    }
    return dist;
}

Vertex* WasteApp::held_karp(const User &w, vector<Vertex *> housesToCollect) {
    float distance;
    float min_dist = 1000000;
    Vertex* centralV;
    Vertex* start = getVertex(w.getHouse().getVertex());

    //For each of the centrals, calculate the distance from the last spot of the shortest path and see if it's minimum
    for (House &c : centrals) {
        Vertex* vert = getVertex(c.getVertex());
        distance = g(start,vert,housesToCollect);
        if (min_dist > distance) {
            min_dist = distance;
            centralV = vert;
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

//Push the vertexes into the stack in postorder
void WasteApp::fillOrder(Vertex *v, stack<Vertex*> &stack){
    v->setVisited(true);
    for(int i = 0; i != v->getAdjacentIds().size(); i++)
    {
        if(!getVertex(getEdge(v->getAdjacentIds()[i])->getVf())->getVisited())
            fillOrder(getVertex(getEdge(v->getAdjacentIds()[i])->getVf()), vertexesRev);
    }

    vertexesRev.push(v);
}

//Kosaraju's algorithm
int WasteApp::conectividade() {
    int ret = 0;

    for (auto &v : vertexMap) {
        v.second->setVisited(false);
    }

    //Fill the stack in postorder
    for (auto &v : vertexMap){
        if(!v.second->getVisited()){
            fillOrder(v.second, vertexesRev);
        }
    }

    Vertex* tmp;

    //Add each vertex to the reverse graph
    for (auto &v : vertexMap) {
        tmp = new Vertex();
        tmp = v.second;
        tmp->clearAdjacentIds();
        vertexesRevGraph.emplace(tmp->getID(), tmp);
    }

    //Add each edge to the reverse graph and to the vertexes' adjacent ids
    for(auto &e : edgeMap){
        Edge* edge = new Edge(e.second->getWeight(), e.second->getID(), e.second->getVf(), e.second->getVi());
        edgesRevGraphMap.emplace(edge->getID(), edge);
        Vertex* vert = getVertexR(edge->getVi());
        vert->addAdjacent(edge->getID());
    }

    for (auto &v : vertexMap) {
        v.second->setVisited(false);
    }

    //In the order that they're placed in the stack, process each vertex to find the strongly connected regions
    while(!vertexesRev.empty()){
        Vertex* v = vertexesRev.top();
        vertexesRev.pop();

        if(!v->getVisited()){
            util(v);
            ret++;
        }
    }
    return ret;
}

//Find each vertex's strongly connected region recursively
void WasteApp::util(Vertex *v) {
    v->setVisited(true);
    for(int i = 0; i != v->getAdjacentIds().size(); i++) {
        Edge* e = getEdgeR(v->getAdjacentIds()[i]);
        Vertex* vert = getVertexR(e->getVf());
        if(!vert->getVisited()) util(vert);
    }
}
