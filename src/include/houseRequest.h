#ifndef SRC_HOUSEREQUEST_H
#define SRC_HOUSEREQUEST_H

#include "spot.h"

class HouseRequest {
    enum type type;
    float quantity;

public:
    HouseRequest(enum type type, float quantity);

    enum type getType() const;

    float getQuantity() const;
};


#endif //SRC_HOUSEREQUEST_H
