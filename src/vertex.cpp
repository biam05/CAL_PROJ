#include "vertex.h"

void Vertex::setDistance(float d) {
    distance = d;
}

vector<int> Vertex::getAdjacentIds() {
    return adjacent_IDs;
}

int Vertex::getID() {
    return ID;
}

int Vertex::getX() {
    return x;
}

int Vertex::getY() {
    return y;
}
