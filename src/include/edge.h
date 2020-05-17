#ifndef CAL_PROJ_EDGES_H
#define CAL_PROJ_EDGES_H

#include "vertex.h"

using namespace std;

class Edge {
    float weight;
    int ID;
    int vi;
    int vf;

public:
    Edge(){
        weight = 0;
        ID = -1;
        vi = -1;
        vf = -1;
    }
    Edge (float w, int id, int v1, int v2) : weight(w), ID(id), vi(v1), vf(v2) {};

    float getWeight();
    int getID();
    int getVi();
    int getVf();
};

#endif //CAL_PROJ_EDGES_H
