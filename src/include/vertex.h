#ifndef CAL_PROJ_VERTEXES_H
#define CAL_PROJ_VERTEXES_H

#include <vector>

using namespace std;

class Vertex {
    float distance;
    vector<int> adjacent_IDs;
    int x;
    int y;
    int ID;

public:
    Vertex () {
        distance = 0;
        ID = -1;
        x = -1;
        y = -1;
    }
    Vertex (int ID, int x, int y) : ID(ID), x(x), y(y) {
        distance = 0;
    };

    void setDistance (float d);

    vector<int> getAdjacentIds();

    void addAdjacent(int id);

    int getID();
    int getX();
    int getY();
};

#endif //CAL_PROJ_VERTEXES_H
