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

float Vertex::getX() {
    return x;
}

float Vertex::getY() {
    return y;
}

void Vertex::addAdjacent(int id) {
    adjacent_IDs.push_back(id);
}
