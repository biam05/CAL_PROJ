#ifndef CAL_PROJ_VERTEXES_H
#define CAL_PROJ_VERTEXES_H

#include <vector>

using namespace std;

class Vertex {
    //distance between the vertex and another one that is being studied
    float distance;
    //boolean to know if the vertex was already visited
    bool visited;
    //vector with the ID's of the edges that are connected to the vertex
    vector<int> adjacent_IDs;
    float x;
    float y;
    int ID;
    int prevEdge;
    int prevHouse;

public:
    int queueIndex = 0; 		// required by MutablePriorityQueue

    Vertex () {
        visited = false;
        distance = 0;
        ID = -1;
        x = -1;
        y = -1;
        prevEdge = -1;
        prevHouse = -1;
    }
    Vertex (int ID, float x, float y) : ID(ID), x(x), y(y) {
        distance = 0;
        visited = false;
        prevEdge = -1;
        prevHouse = -1;
    };

    void setDistance (float d);

    void setVisited(bool v);

    void setPrevEdge(int e);

    void setPrevHouse(int v);

    vector<int> getAdjacentIds();

    void addAdjacent(int id);

    void clearAdjacentIds();

    int getID() const;
    bool getVisited();
    float getDistance();
    float getX();
    float getY();
    int getPrevEdge();
    int getPrevHouse();

    //Operator that checks if the distance from the vertex to another is lower than the distance from the given
    //vertex to another
    bool operator<(Vertex & vertex) const;
};

#endif //CAL_PROJ_VERTEXES_H
