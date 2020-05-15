#ifndef CAL_PROJ_VERTEXES_H
#define CAL_PROJ_VERTEXES_H

using namespace std;

class Vertex {
    float distance;
    vector<Edge> adjacent;

public:
    Vertex (float d, vector<Edge> adj) : distance(d), adjacent(adj) {};

    void set_distance (float d);

    vector<Edge> get_adjacent();
};

#endif //CAL_PROJ_VERTEXES_H
