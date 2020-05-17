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
        ID = 0;
        x = 0;
        y = 0;
    }
    Vertex (int ID, int x, int y) : ID(ID), x(x), y(y) {
        distance = 0;
    };

    void setDistance (float d);

    vector<int> getAdjacentIds();

    int getID();
    int getX();
    int getY();
};

#endif //CAL_PROJ_VERTEXES_H
