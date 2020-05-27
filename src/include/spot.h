#ifndef CAL_PROJ_SPOTS_H
#define CAL_PROJ_SPOTS_H

using namespace std;

enum type {PLASTIC, PAPER, GLASS, ORGANIC};

class Spot {
    enum type type;
    float quantity;
    float max_quantity;
    int vertex;

public:
    Spot (enum type t, float q, float max_q, int v) : type(t), quantity(q), max_quantity(max_q), vertex(v) {};

    void setQuantity(float q);

    enum type getType();
    float getQuantity();
    int getVertex();

    //Function that checks if the quantity of the spot added with the user's waste quantity isn't higher than it's max quantity
    bool fits(float q);
};

#endif //CAL_PROJ_SPOTS_H
