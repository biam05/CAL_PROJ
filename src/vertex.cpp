#include "vertex.h"

void Vertex::setDistance(float d) {
    distance = d;
}

vector<int> Vertex::getAdjacentIds() {
    return adjacent_IDs;
}
