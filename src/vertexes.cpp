#include "vertexes.h"

void Vertex::set_distance(float d) {
    distance = d;
}

vector<int> Vertex::get_adjacent() {
    return adjacent_IDs;
}
