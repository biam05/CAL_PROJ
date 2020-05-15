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

    void set_distance (float d);

    vector<int> get_adjacent();
};

#endif //CAL_PROJ_VERTEXES_H
