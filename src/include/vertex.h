#ifndef CAL_PROJ_VERTEXES_H
#define CAL_PROJ_VERTEXES_H

#include <vector>

using namespace std;

class Vertex {
    float distance;
    vector<int> adjacent_IDs;

public:
    Vertex () {
        distance = 0;
    }
    Vertex (float d, vector<int> adj) : distance(d), adjacent_IDs(adj) {};

    void setDistance (float d);

    vector<int> getAdjacentIds();
};

#endif //CAL_PROJ_VERTEXES_H
