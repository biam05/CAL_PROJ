#ifndef CAL_PROJ_EDGES_H
#define CAL_PROJ_EDGES_H

#include "vertexes.h"

using namespace std;

class Edge {
    float weight;
    int ID;
    Vertex vi;
    Vertex vf;

public:
    Edge(){
        weight = 0;
        ID = -1;
    }
    Edge (float w, int id, Vertex v1, Vertex v2) : weight(w), ID(id), vi(v1), vf(v2) {};

    float get_weight();
    int get_ID();
    Vertex get_vi();
    Vertex get_vf();
};

#endif //CAL_PROJ_EDGES_H
