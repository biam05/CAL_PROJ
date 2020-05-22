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

void Vertex::setVisited(bool v) {
    visited = v;
}

bool Vertex::getVisited() {
    return visited;
}

float Vertex::getDistance() {
    return distance;
}

bool Vertex::operator<(Vertex &vertex) const {
    return distance < vertex.distance;
}

int Vertex::getPrevEdge() {
    return prevEdge;
}

void Vertex::setPrevEdge(int e) {
    prevEdge = e;

}
