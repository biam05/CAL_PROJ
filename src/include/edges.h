#ifndef CAL_PROJ_EDGES_H
#define CAL_PROJ_EDGES_H

#endif //CAL_PROJ_EDGES_H

using namespace std;

class Edge {
    float weight;
    int ID;
    Vertex vi;
    Vertex vf;

public:
    Edge (float w, int id, Vertex v1, Vertex v2) : weight(w), ID(id), vi(v1); vf(v2) {};

    float get_weight();
    float get_ID();
    float get_vi();
    float get_vf();
};