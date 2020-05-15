#ifndef CAL_PROJ_EDGES_H
#define CAL_PROJ_EDGES_H

#include "vertex.h"

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

    float getWeight();
    int getId();
    Vertex getVi();
    Vertex getVf();
};

#endif //CAL_PROJ_EDGES_H
